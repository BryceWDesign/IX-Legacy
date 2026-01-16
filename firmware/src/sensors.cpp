// File: firmware/src/sensors.cpp
#include "sensors.h"

// NOTE: This file intentionally contains placeholder reads.
// Replace with real ADC/current-monitor reads tied to your hardware.

void Sensors::begin() {
  // init ADC, I2C, SPI, etc. (future)
}

bool Sensors::sane_float(float v) const {
  // Basic NaN/Inf guard without <cmath> dependencies in some embedded toolchains
  return (v == v) && (v > -1.0e9f) && (v < 1.0e9f);
}

bool Sensors::read_telemetry(Telemetry& t) {
  // ---- PLACEHOLDERS ----
  // In v0 we return plausible “zeros” to validate the logging/state machine wiring.
  // When bound to hardware, replace each field with real measurements.

  t.v_cap_v = 0.0f;
  t.i_cap_a = 0.0f;
  t.t_cap_c = 25.0f;

  t.v_rail_5v_v = 0.0f;
  t.i_rail_5v_a = 0.0f;

  t.t_conv_c = 25.0f;

  t.v_mod1_v = 0.0f;
  t.i_mod1_a = 0.0f;
  t.v_mod2_v = 0.0f;
  t.i_mod2_a = 0.0f;

  // sanity check
  return sane_float(t.v_cap_v) && sane_float(t.i_cap_a) && sane_float(t.t_cap_c)
      && sane_float(t.t_conv_c) && sane_float(t.v_mod1_v) && sane_float(t.i_mod1_a);
}
