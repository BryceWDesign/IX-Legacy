// File: firmware/src/main.cpp
#include "config.h"
#include "types.h"
#include "sensors.h"
#include "logger.h"
#include "state_machine.h"

#include "triad_link.h"
#include "energy_router.h"

static uint32_t now_ms() {
  static uint32_t fake = 0;
  fake += CONTROL_INTERVAL_MS;
  return fake;
}

int main() {
  Sensors sensors;
  Logger logger;
  StateMachine sm;

  TriadLink triad;
  EnergyRouter router;

  sensors.begin();
  logger.begin();
  sm.reset();
  triad.begin();
  router.reset();

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
      out = t;
      out.fault = FaultCode::SENSOR_INVALID;
      out.state = SystemState::FAULT_LATCHED;
      out.derate = 0.0f;
    } else {
      // run the core state machine first (safety-first)
      sm.tick(t, out);

      // tick triad link (no-op stub in v0)
      triad.tick(n, out);

      // router policy: decides rail gating and dump intent (policy only)
      RouterInputs rin{};
      rin.local = out;

      rin.have_buffer_master = triad.have_buffer_master();
      rin.have_conversion_master = triad.have_conversion_master();
      rin.have_sense_master = triad.have_sense_master();
      if (rin.have_buffer_master) rin.buffer_master = triad.buffer_master();
      if (rin.have_conversion_master) rin.conversion_master = triad.conversion_master();
      if (rin.have_sense_master) rin.sense_master = triad.sense_master();

      RouterOutputs rout = router.compute(rin);

      // v0: annotate telemetry with the router's power_limit as derate refinement
      // Later: bind allow_rails / dump to GPIO and override sm outputs appropriately.
      out.derate = rout.power_limit;

      // NOTE: We intentionally do not directly override sm's safety decisions in v0.
      // Hardware binding and arbitration policy is a future commit once transport exists.
      (void)rout;
    }

    if ((n - last_log_ms) >= LOG_INTERVAL_MS) {
      last_log_ms = n;
      logger.log_row(out);
    }
  }

  return 0;
}
