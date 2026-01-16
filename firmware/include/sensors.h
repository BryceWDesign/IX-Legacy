// File: firmware/include/sensors.h
#pragma once
#include "types.h"

// Sensor layer is a stub in v0.
// Bind these to ADC/current monitors/temperature sensors in later hardware commits.

class Sensors {
public:
  void begin();
  bool read_telemetry(Telemetry& t);   // returns false if sensors invalid/out-of-range

private:
  bool sane_float(float v) const;
};
