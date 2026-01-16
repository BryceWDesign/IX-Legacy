// File: firmware/src/main.cpp
#include "config.h"
#include "types.h"
#include "sensors.h"
#include "logger.h"
#include "state_machine.h"

// This is a platform-agnostic main loop scaffold.
// Bind millis(), delays, and serial init to your target platform.

static uint32_t now_ms() {
  // replace with millis() on Arduino/ESP32, HAL_GetTick(), etc.
  static uint32_t fake = 0;
  fake += CONTROL_INTERVAL_MS;
  return fake;
}

int main() {
  Sensors sensors;
  Logger logger;
  StateMachine sm;

  sensors.begin();
  logger.begin();
  sm.reset();
  logger.log_header();

  uint32_t last_log_ms = 0;
  uint32_t last_tick_ms = 0;

  Telemetry t{};
  Telemetry out{};

  while (true) {
    uint32_t n = now_ms();
    uint32_t dt = (n - last_tick_ms);
    last_tick_ms = n;

    t.ts_ms = n;
    t.dt_ms = dt;

    bool ok = sensors.read_telemetry(t);
    if (!ok) {
      // Sensor invalid -> latch fault
      out = t;
      out.fault = FaultCode::SENSOR_INVALID;
      out.state = SystemState::FAULT_LATCHED;
      out.derate = 0.0f;
    } else {
      sm.tick(t, out);
      // NOTE: sm control outputs (rails/dump/precharge/bypass) must be bound to GPIO in later commits.
    }

    // Log at fixed interval
    if ((n - last_log_ms) >= LOG_INTERVAL_MS) {
      last_log_ms = n;
      logger.log_row(out);
    }

    // delay/sleep would occur here on real platform
  }

  return 0;
}
