// File: firmware/src/triad_link.cpp
#include "triad_link.h"

void TriadLink::begin() {
  // init RS-485/CAN (future)
  have_bm_ = have_cm_ = have_sm_ = false;
  last_heartbeat_ms_ = 0;
}

void TriadLink::tick(uint32_t now_ms, const Telemetry& local) {
  (void)local;
  // v0: no real transport. This is a structural stub.
  // Future: broadcast heartbeat and role telemetry; update bm_/cm_/sm_ on receive.

  // keep placeholders invalid unless real comms implemented
  (void)now_ms;
}
