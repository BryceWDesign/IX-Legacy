# File: docs/validation/TRI_CORE_TESTS.md
# IX-Legacy — Tri-Core Router Validation Tests (v0)

## 0) Purpose
These tests prove the Tri-Core Router invariants:
- no backfeed,
- safe precharge,
- safe dump/discharge,
- energy accounting closure,
- stable rail gating (no chatter),
- triad interconnect safety.

All tests must be documented with:
- raw logs (CSV),
- calibration file,
- filled report (REPORT_TEMPLATE),
- reconciliation numbers.

## 1) Test: Backfeed (module-level)
### Goal
Prove that no harvester module is reverse-driven by the bus.

### Setup
- Connect 2+ modules (or simulated sources) to the bus.
- Charge storage to a stable bus/cap voltage where reverse-driving would be detectable.

### Procedure
1) Enable bus/storage so V_cap is above a typical module output.
2) Disconnect (or disable) one module while leaving others active.
3) Log module boundary current for the disconnected module.

### Pass criteria
- i_modX_a does not go negative beyond noise bounds.
- No module voltage rises abnormally due to backfeed.

## 2) Test: Precharge (storage connection)
### Goal
Prove that connecting large capacitance does not cause a damaging inrush.

### Setup
- Start with storage disconnected (or bypass open).
- Instrument V_bus (recommended), V_cap, and I_cap.

### Procedure
1) Close precharge path (resistor) and log V_cap rise vs time.
2) Confirm ΔV convergence and then close bypass.
3) Observe I_cap transient at bypass closure.

### Pass criteria
- Precharge completes without fault.
- Bypass closure does not produce uncontrolled current spikes.
- PRECHARGE_TIMEOUT does not trigger in a normal setup.

## 3) Test: Dump / Service discharge
### Goal
Prove storage can be discharged safely and verifiably.

### Setup
- Charge supercap bank to a defined V_cap (within safe limits).
- Instrument V_cap and (if possible) dump resistor temperature.

### Procedure
1) Engage DUMP_EN and log V_cap decay.
2) Continue until V_cap reaches a defined “safe service voltage.”

### Pass criteria
- V_cap decays to safe voltage in the documented time.
- Dump components remain within thermal limits.
- Discharge is repeatable between runs.

## 4) Test: Energy accounting closure (single device)
### Goal
Demonstrate Energy Truth reconciliation closes:
E_in ≈ ΔE_cap + E_out + losses.

### Setup
- Choose one module and a stable environment (vibration/ΔT/E-field).
- Keep rails OFF (harvest-only) for the first phase, then enable a defined load.

### Procedure
Phase A (Harvest-only):
- log E_in and ΔE_cap.
Phase B (Regulate/load):
- enable rails and defined load profile; log E_out.

### Pass criteria
- E_loss is non-negative and explainable.
- No unexplained “energy creation” artifacts.

## 5) Test: Rail gating and load-shed stability
### Goal
Prove rails enable only when buffer allows, and shed cleanly on low V_cap or thermal derate.

### Setup
- Configure a load that would drain the buffer if left on continuously.
- Instrument V_cap and rail voltages.

### Procedure
1) Allow buffer to charge.
2) Enable rail gating.
3) Observe enable/disable behavior as V_cap rises/falls.

### Pass criteria
- No rapid chatter/oscillation around thresholds (hysteresis must be added if needed).
- Loads shed predictably and safely.

## 6) Test: Triad hot-plug (Gankyil interconnect)
### Goal
Prove connecting/disconnecting a triad node does not collapse the backbone and does not backfeed.

### Setup
- Buffer Master hosts storage; other units connect via OR + fuse + precharge.
- Instrument per-unit boundary currents where possible.

### Procedure
1) Connect Unit B via precharge; confirm stable backbone.
2) Connect Unit C via precharge.
3) Disconnect Unit B (or open bypass) and observe reverse currents.

### Pass criteria
- No backbone collapse beyond allowed transient.
- No reverse current into disconnected unit.
- Fault isolation works (unit fault does not take down others).

## 7) Required deliverables per test
For each test, include:
- run folder: runs/YYYY-MM-DD_testname/
- raw_log.csv
- calibration.json
- report.md (filled template)
- photos/diagram of setup (recommended)
