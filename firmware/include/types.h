// File: firmware/include/types.h
#pragma once
#include <stdint.h>

enum class SystemState : uint8_t {
  SAFE_START = 0,
  HARVEST_ONLY,
  CHARGE,
  REGULATE,
  LOAD_SHED,
  FAULT_LATCHED
};

enum class FaultCode : uint16_t {
  NONE = 0,
  PRECHARGE_TIMEOUT = 1,
  OVERVOLTAGE = 2,
  THERMAL_CONV_CRITICAL = 3,
  THERMAL_CAP_CRITICAL = 4,
  SENSOR_INVALID = 5,
  REVERSE_CURRENT_DETECTED = 6
};

struct Telemetry {
  // time
  uint32_t ts_ms = 0;
  uint32_t dt_ms = 0;

  // storage
  float v_cap_v = 0.0f;
  float i_cap_a = 0.0f;
  float t_cap_c = 0.0f;

  // conversion / rails (v0: only 5V rail is represented; add 12V later)
  float v_rail_5v_v = 0.0f;
  float i_rail_5v_a = 0.0f;

  // converter hotspot
  float t_conv_c = 0.0f;

  // module boundaries (v0: two generic module channels; expand later)
  float v_mod1_v = 0.0f;
  float i_mod1_a = 0.0f;
  float v_mod2_v = 0.0f;
  float i_mod2_a = 0.0f;

  // state/fault
  SystemState state = SystemState::SAFE_START;
  FaultCode fault = FaultCode::NONE;

  // derating factor (1.0 = full, 0.0 = off)
  float derate = 1.0f;
};
