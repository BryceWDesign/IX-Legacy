// File: firmware/include/triad_link.h
#pragma once
#include "types.h"
#include "triad_config.h"

// TriadLink is a stub for the RS-485/CAN telemetry exchange.
// In v0 it provides a structure to plug into later without changing router logic.

class TriadLink {
public:
  void begin();
  void tick(uint32_t now_ms, const Telemetry& local);

  // Latest remote snapshots (validity flags)
  bool have_buffer_master() const { return have_bm_; }
  bool have_conversion_master() const { return have_cm_; }
  bool have_sense_master() const { return have_sm_; }

  const Telemetry& buffer_master() const { return bm_; }
  const Telemetry& conversion_master() const { return cm_; }
  const Telemetry& sense_master() const { return sm_; }

private:
  bool have_bm_ = false;
  bool have_cm_ = false;
  bool have_sm_ = false;

  Telemetry bm_{};
  Telemetry cm_{};
  Telemetry sm_{};

  uint32_t last_heartbeat_ms_ = 0;

  // Placeholder: implement send/receive on RS-485/CAN later
};
