// File: firmware/include/energy_router.h
#pragma once
#include "types.h"
#include "triad_config.h"

// EnergyRouter is the "Tri-Core Router" policy layer that decides:
// - when rails may be enabled (REGULATE),
// - when to shed loads (LOAD_SHED),
// - how to behave in triad roles (Buffer/Conversion/Sense).
//
// v0: policy-only scaffold. Real comms and GPIO binding are future work.

struct RouterInputs {
  Telemetry local;     // local telemetry snapshot
  // In triad mode these would be the latest remote snapshots:
  Telemetry buffer_master;     // authoritative V_cap/I_cap
  Telemetry conversion_master; // authoritative rails status
  Telemetry sense_master;      // authoritative fault/derate intent

  bool have_buffer_master = false;
  bool have_conversion_master = false;
  bool have_sense_master = false;
};

struct RouterOutputs {
  // Desired control outputs (policy):
  bool allow_rails = false;
  bool force_load_shed = false;
  bool force_dump = false;      // typically on overvoltage
  float power_limit = 1.0f;     // 0..1 scaling, derived from derate
};

class EnergyRouter {
public:
  void reset();
  RouterOutputs compute(const RouterInputs& in);

private:
  RouterOutputs out_{};
  float clamp01(float v) const;
};
