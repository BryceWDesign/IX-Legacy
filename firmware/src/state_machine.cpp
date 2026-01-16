// File: firmware/src/state_machine.cpp
#include "state_machine.h"

void StateMachine::reset() {
  state_ = SystemState::SAFE_START;
  fault_ = FaultCode::NONE;
  derate_ = 1.0f;

  rails_enabled_ = false;
  dump_enabled_ = false;
  precharge_enabled_ = false;
  bypass_enabled_ = false;

  precharge_start_ms_ = 0;
  dv_below_start_ms_ = 0;
  precharge_in_progress_ = false;
}

void StateMachine::latch_fault(FaultCode f) {
  if (fault_ != FaultCode::NONE) return; // keep first/root cause in v0
  fault_ = f;
  state_ = SystemState::FAULT_LATCHED;

  rails_enabled_ = false;
  precharge_enabled_ = false;
  bypass_enabled_ = false;
  // dump load may be enabled depending on fault context (handled below)
}

bool StateMachine::thermal_critical(const Telemetry& t) const {
  return (t.t_conv_c >= T_CONV_RED_C) || (t.t_cap_c >= T_CAP_RED_C);
}

bool StateMachine::thermal_amber(const Telemetry& t) const {
  return (t.t_conv_c >= T_CONV_AMBER_C) || (t.t_cap_c >= T_CAP_AMBER_C);
}

void StateMachine::compute_derate(const Telemetry& t) {
  // v0: simple piecewise derate
  if (thermal_critical(t)) {
    derate_ = 0.0f;
    return;
  }
  if (!thermal_amber(t)) {
    derate_ = 1.0f;
    return;
  }

  // Linear derate between AMBER and RED for converter hotspot (dominant)
  float span = (T_CONV_RED_C - T_CONV_AMBER_C);
  float over = (t.t_conv_c - T_CONV_AMBER_C);
  float d = 1.0f;
  if (span > 0.1f) {
    d = 1.0f - (over / span);
  }
  if (d < 0.2f) d = 0.2f; // keep minimal telemetry power if possible
  if (d > 1.0f) d = 1.0f;
  derate_ = d;
}

void StateMachine::tick(const Telemetry& in, Telemetry& out) {
  // Start with input telemetry and annotate with state outputs
  out = in;
  out.state = state_;
  out.fault = fault_;
  out.derate = derate_;

  // Hard faults first
  if (thermal_critical(in)) {
    latch_fault((in.t_conv_c >= T_CONV_RED_C) ? FaultCode::THERMAL_CONV_CRITICAL
                                             : FaultCode::THERMAL_CAP_CRITICAL);
  }
  if (in.v_cap_v >= V_CAP_OVERVOLT_V) {
    latch_fault(FaultCode::OVERVOLTAGE);
  }

  // Derating update
  compute_derate(in);

  // If faulted, enforce safe outputs
  if (state_ == SystemState::FAULT_LATCHED) {
    rails_enabled_ = false;
    precharge_enabled_ = false;
    bypass_enabled_ = false;

    // If overvoltage, enable dump (concept). Otherwise keep dump off by default.
    dump_enabled_ = (fault_ == FaultCode::OVERVOLTAGE);
    out.state = state_;
    out.fault = fault_;
    out.derate = derate_;
    return;
  }

  // State transitions (v0 policy)
  switch (state_) {
    case SystemState::SAFE_START:
      // In v0, we immediately move to HARVEST_ONLY.
      rails_enabled_ = false;
      dump_enabled_ = false;
      precharge_enabled_ = false;
      bypass_enabled_ = false;
      state_ = SystemState::HARVEST_ONLY;
      break;

    case SystemState::HARVEST_ONLY:
      // Only harvest into storage; rails disabled.
      rails_enabled_ = false;
      dump_enabled_ = false;

      // If storage is below rail minimum, stay here (charging).
      // If storage is high enough, we may proceed to REGULATE.
      if (in.v_cap_v >= V_CAP_MIN_ENABLE_RAILS_V && derate_ > 0.0f) {
        state_ = SystemState::CHARGE; // precharge + readiness gate before regulate
      }
      break;

    case SystemState::CHARGE: {
      // Precharge scaffold:
      // In v0 we assume V_bus is not instrumented; treat precharge as time-based placeholder.
      // Later commits will add V_bus measurement and true ΔV logic.
      rails_enabled_ = false;
      dump_enabled_ = false;

      if (!precharge_in_progress_) {
        precharge_in_progress_ = true;
        precharge_start_ms_ = in.ts_ms;
        dv_below_start_ms_ = in.ts_ms;
        precharge_enabled_ = true;
        bypass_enabled_ = false;
      }

      // Placeholder dwell/timeout logic
      if ((in.ts_ms - precharge_start_ms_) > PRECHARGE_TIMEOUT_MS) {
        latch_fault(FaultCode::PRECHARGE_TIMEOUT);
        break;
      }

      // After dwell, close bypass and proceed
      if ((in.ts_ms - dv_below_start_ms_) > PRECHARGE_DWELL_MS) {
        precharge_enabled_ = false;
        bypass_enabled_ = true;
        precharge_in_progress_ = false;
        state_ = SystemState::REGULATE;
      }
      break;
    }

    case SystemState::REGULATE:
      // Enable rails when buffer and thermal allow
      if (in.v_cap_v < V_CAP_MIN_ENABLE_RAILS_V || derate_ <= 0.0f) {
        state_ = SystemState::LOAD_SHED;
        rails_enabled_ = false;
      } else {
        rails_enabled_ = true;
      }
      dump_enabled_ = false;
      precharge_enabled_ = false;
      bypass_enabled_ = true;
      break;

    case SystemState::LOAD_SHED:
      // Reduced service mode: rails off by default in v0.
      // Later commits can implement “telemetry-only rail” or duty-cycled rail enable.
      rails_enabled_ = false;
      dump_enabled_ = false;

      // If buffer recovers and thermal is ok, return to CHARGE/REGULATE path
      if (in.v_cap_v >= V_CAP_MIN_ENABLE_RAILS_V && derate_ > 0.2f && !thermal_amber(in)) {
        state_ = SystemState::CHARGE;
      }
      break;

    default:
      // Defensive: unknown state -> safe mode
      state_ = SystemState::FAULT_LATCHED;
      latch_fault(FaultCode::SENSOR_INVALID);
      break;
  }

  // annotate outputs
  out.state = state_;
  out.fault = fault_;
  out.derate = derate_;
}
