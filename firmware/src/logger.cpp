// File: firmware/src/logger.cpp
#include "logger.h"

// NOTE: Serial output is pseudocode for portability.
// Replace with your platform's serial/printf implementation.

static void serial_print(const char* s) {
  (void)s;
  // hook to Serial.print / printf / UART write
}

static void serial_print_float(float v) {
  (void)v;
  // hook to Serial.print(v, decimals) or printf("%0.3f", v)
}

static void serial_print_uint(uint32_t v) {
  (void)v;
  // hook to Serial.print(v) or printf("%lu", (unsigned long)v)
}

void Logger::begin() {
  // init serial / sd (future)
}

void Logger::log_header() {
  if (header_written_) return;
  // Canonical fields from docs/validation/LOG_FIELDS.md (minimal viable subset)
  serial_print("ts_ms,dt_ms,");
  serial_print("v_cap_v,i_cap_a,t_cap_c,");
  serial_print("v_rail_5v_v,i_rail_5v_a,");
  serial_print("t_conv_c,");
  serial_print("v_mod1_v,i_mod1_a,v_mod2_v,i_mod2_a,");
  serial_print("state,fault,derate\n");
  header_written_ = true;
}

static const char* state_to_str(SystemState s) {
  switch (s) {
    case SystemState::SAFE_START:   return "SAFE_START";
    case SystemState::HARVEST_ONLY: return "HARVEST_ONLY";
    case SystemState::CHARGE:       return "CHARGE";
    case SystemState::REGULATE:     return "REGULATE";
    case SystemState::LOAD_SHED:    return "LOAD_SHED";
    case SystemState::FAULT_LATCHED:return "FAULT_LATCHED";
    default: return "UNKNOWN";
  }
}

static const char* fault_to_str(FaultCode f) {
  switch (f) {
    case FaultCode::NONE: return "NONE";
    case FaultCode::PRECHARGE_TIMEOUT: return "PRECHARGE_TIMEOUT";
    case FaultCode::OVERVOLTAGE: return "OVERVOLTAGE";
    case FaultCode::THERMAL_CONV_CRITICAL: return "THERMAL_CONV_CRITICAL";
    case FaultCode::THERMAL_CAP_CRITICAL: return "THERMAL_CAP_CRITICAL";
    case FaultCode::SENSOR_INVALID: return "SENSOR_INVALID";
    case FaultCode::REVERSE_CURRENT_DETECTED: return "REVERSE_CURRENT_DETECTED";
    default: return "UNKNOWN";
  }
}

void Logger::log_row(const Telemetry& t) {
  if (!header_written_) log_header();

  serial_print_uint(t.ts_ms); serial_print(",");
  serial_print_uint(t.dt_ms); serial_print(",");

  serial_print_float(t.v_cap_v); serial_print(",");
  serial_print_float(t.i_cap_a); serial_print(",");
  serial_print_float(t.t_cap_c); serial_print(",");

  serial_print_float(t.v_rail_5v_v); serial_print(",");
  serial_print_float(t.i_rail_5v_a); serial_print(",");

  serial_print_float(t.t_conv_c); serial_print(",");

  serial_print_float(t.v_mod1_v); serial_print(",");
  serial_print_float(t.i_mod1_a); serial_print(",");
  serial_print_float(t.v_mod2_v); serial_print(",");
  serial_print_float(t.i_mod2_a); serial_print(",");

  serial_print(state_to_str(t.state)); serial_print(",");
  serial_print(fault_to_str(t.fault)); serial_print(",");
  serial_print_float(t.derate);
  serial_print("\n");
}
