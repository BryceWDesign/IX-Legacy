// File: firmware/include/state_machine.h
#pragma once
#include "types.h"
#include "config.h"

class StateMachine {
public:
  void reset();
  void tick(const Telemetry& in, Telemetry& out);

  // control outputs (stubs; bind to hardware later)
  bool rails_enabled() const { return rails_enabled_; }
  bool dump_enabled() const { return dump_enabled_; }
  bool precharge_enabled() const { return precharge_enabled_; }
  bool bypass_enabled() const { return bypass_enabled_; }

private:
  // internal state
  SystemState state_ = SystemState::SAFE_START;
  FaultCode fault_ = FaultCode::NONE;

  // derating
  float derate_ = 1.0f;

  // precharge tracking
  uint32_t precharge_start_ms_ = 0;
  uint32_t dv_below_start_ms_ = 0;
  bool precharge_in_progress_ = false;

  // outputs
  bool rails_enabled_ = false;
  bool dump_enabled_ = false;
  bool precharge_enabled_ = false;
  bool bypass_enabled_ = false;

  // helpers
  void latch_fault(FaultCode f);
  void compute_derate(const Telemetry& t);
  bool thermal_critical(const Telemetry& t) const;
  bool thermal_amber(const Telemetry& t) const;
};
