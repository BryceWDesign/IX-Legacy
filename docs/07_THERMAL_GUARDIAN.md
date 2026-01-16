# File: docs/07_THERMAL_GUARDIAN.md
# IX-Legacy — ThermalGuardian Specification (v0)

## 0) Purpose
ThermalGuardian prevents IX-Legacy from cooking itself, and prevents “performance” claims
that only exist for a few seconds before thermal runaway.

ThermalGuardian enforces:
- derating (soft limits) before damage,
- hard shutdown (critical limits),
- logging of thermal behavior for validation.

## 1) Thermal control philosophy (non-negotiable)
T1) Measure real hotspot temperatures (not “ambient near board” only).
T2) Derate power delivery before critical thresholds.
T3) Hard shutdown must override all other goals.
T4) Treat heat as data: log temperature, power, and duty cycle together.

## 2) Required sensors (v0)
### 2.1 Converter hotspot sensor (required)
- Location: near MOSFET/inductor/heatsink region (the hottest spot).
- Signal: t_conv_c

### 2.2 Storage temperature sensor (required)
- Location: near supercap bank body (not the coolest edge).
- Signal: t_cap_c

### 2.3 Optional module hotspot sensors (recommended)
- For modules with diodes/MPPT ICs or switching stages.

## 3) Derating model (generic, environment-agnostic)
ThermalGuardian uses three regions:
- Green: full operation permitted
- Amber: derating active (reduce load / reduce converter duty / disable nonessential rails)
- Red: critical shutdown (disable conversion/load, optionally engage dump path if overvoltage exists)

### 3.1 Thresholds
Do NOT hardcode component-specific values in v0 docs without referencing a concrete BOM and
datasheets. Instead, define them as parameters:

- T_CONV_AMBER_C  (start derating)
- T_CONV_RED_C    (shutdown)
- T_CAP_AMBER_C   (start derating)
- T_CAP_RED_C     (shutdown)

A later hardware commit will bind these to real components.

### 3.2 Derating actions (ordered)
When any sensor exceeds AMBER:
1) Reduce output power limit (software current limit) if available
2) Disable high-load rails (prioritize keeping telemetry alive)
3) Reduce switching frequency or duty (if supported)
4) Increase cooling (fan/pump PWM) if present

When any sensor exceeds RED:
1) Disable conversion outputs immediately
2) Latch thermal fault
3) Maintain telemetry logging if buffer permits
4) Allow recovery only when temperature falls below a reset threshold and an explicit reset occurs

### 3.3 Hysteresis (required)
To avoid oscillation:
- Use a reset threshold below AMBER for recovery:
  - T_CONV_RESET_C < T_CONV_AMBER_C
  - T_CAP_RESET_C  < T_CAP_AMBER_C
- Require dwell time below reset threshold before clearing the fault.

## 4) Cooling hardware control (optional but recommended)
ThermalGuardian may control:
- FAN_PWM (forced convection)
- PUMP_PWM (if liquid loop exists)
- VALVE_STATE (if using a heat exchanger path)

Rule: Cooling control must not create a net-energy illusion. If cooling power is supplied
by the device itself, it must be measured as part of output consumption.

## 5) Thermal logging requirements (must be in logs)
- t_conv_c, t_cap_c (required)
- v_cap_v, i_cap_a
- v_rail_x, i_rail_x
- state (normal/derating/shutdown)
- derating factor or power limit value

This allows correlating heat rise with delivered watts and proving safe operation.

## 6) Validation tests (v0)
- Step-load test: apply a defined load and observe derating behavior
- Steady-state test: operate at the highest safe continuous output and confirm thermal stability
- Fault test: simulate sensor over-temp (or safely heat hotspot) and verify shutdown + latch

Test results must be recorded per `docs/04_ENERGY_TRUTH_PROTOCOL.md`.
