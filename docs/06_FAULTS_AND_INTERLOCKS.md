# File: docs/06_FAULTS_AND_INTERLOCKS.md
# IX-Legacy — Faults & Interlocks (v0)

## 0) Purpose
Define hard constraints that keep the platform safe and honest.

## 1) Interlocks (must be enforced)
I1) Conversion enable interlock
- Regulators may only enable when:
  - V_cap is above a defined minimum,
  - ThermalGuardian is below derating threshold,
  - no latched faults are present.

I2) Precharge interlock
- Main bus-to-storage bypass must not close unless ΔV is below threshold.

I3) Dump-load interlock
- Dump path must be available whenever the supercap bank is connected.
- In fault states (overvoltage/thermal), dump may be forced on.

I4) Backfeed detection interlock (recommended)
- If reverse current is detected across OR’ing, isolate that branch and latch fault.

## 2) Fault latching policy
- Electrical safety faults latch by default (overvoltage, reverse current, precharge timeout).
- Thermal critical latches until temperature falls below a safe reset threshold and an explicit
  recovery action occurs.

## 3) Recovery actions (examples)
- Manual reset switch (physical)
- Firmware command in controlled environment
- Service procedure after inspection

## 4) Telemetry requirements
Every fault must be logged with:
- timestamp
- active state
- relevant voltages/currents/temperatures
- recovery action if performed

This ensures post-mortem analysis and prevents “mystery behavior.”
