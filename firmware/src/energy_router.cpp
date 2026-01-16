// File: firmware/src/energy_router.cpp
#include "energy_router.h"
#include "config.h"

void EnergyRouter::reset() {
  out_ = {};
  out_.allow_rails = false;
  out_.force_load_shed = false;
  out_.force_dump = false;
  out_.power_limit = 1.0f;
}

float EnergyRouter::clamp01(float v) const {
  if (v < 0.0f) return 0.0f;
  if (v > 1.0f) return 1.0f;
  return v;
}

RouterOutputs EnergyRouter::compute(const RouterInputs& in) {
  // Default: conservative.
  out_.allow_rails = false;
  out_.force_load_shed = false;
  out_.force_dump = false;

  // Use local derate as baseline.
  float derate = clamp01(in.local.derate);
  out_.power_limit = derate;

  // In triad mode, conversion decisions must respect Buffer + Sense.
  if (TRIAD_ROLE == TriadRole::ROLE_SINGLE) {
    // Single device policy:
    // - allow rails only if Vcap sufficient and derate > 0
    out_.allow_rails = (in.local.v_cap_v >= V_CAP_MIN_ENABLE_RAILS_V) && (derate > 0.0f);
    out_.force_load_shed = (in.local.v_cap_v < V_CAP_MIN_ENABLE_RAILS_V) || (derate < 0.3f);
    out_.force_dump = (in.local.v_cap_v >= V_CAP_OVERVOLT_V);
    return out_;
  }

  // Triad policy (v0): prefer authoritative sources when present.
  float vcap = in.local.v_cap_v;
  FaultCode fault = in.local.fault;

  if (in.have_buffer_master) {
    vcap = in.buffer_master.v_cap_v;
  }
  if (in.have_sense_master) {
    // Sense master may reduce power limit (derate) or flag faults.
    derate = clamp01(in.sense_master.derate);
    out_.power_limit = derate;
    fault = in.sense_master.fault;
  }

  // Fault overrides
  if (fault != FaultCode::NONE) {
    out_.allow_rails = false;
    out_.force_load_shed = true;
    out_.force_dump = (fault == FaultCode::OVERVOLTAGE);
    out_.power_limit = 0.0f;
    return out_;
  }

  // Allow rails only if buffer supports it and derate allows.
  out_.allow_rails = (vcap >= V_CAP_MIN_ENABLE_RAILS_V) && (derate > 0.0f);

  // Load shed if buffer low or derate low.
  out_.force_load_shed = (vcap < V_CAP_MIN_ENABLE_RAILS_V) || (derate < 0.3f);

  // Dump if overvoltage (prefer buffer master truth)
  out_.force_dump = (vcap >= V_CAP_OVERVOLT_V);

  return out_;
}
