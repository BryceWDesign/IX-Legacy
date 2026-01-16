# File: docs/validation/REPORT_TEMPLATE.md
# IX-Legacy — Validation Report Template (v0)

## Run ID
- run_id:
- date:
- operator:
- device build/rev:
- firmware version:
- module set present: (A E-field / B vibration / C TEG / R RF tiles)

## Environment description (required)
- Location (indoor/outdoor, near machinery, etc.):
- Vibration source description (if Module B used):
  - qualitative description:
  - optional measured: dominant freq band / approximate acceleration:
- Thermal gradient description (if Module C used):
  - hot-side source:
  - cold-side sink:
  - t_hot_c:
  - t_cold_c:
  - ΔT:
- Lighting conditions (if PV present):
- E-field proximity description (if Module A used):
- RF environment notes (if Module R used):
  - nearby transmitters / known bands (if known):

## System configuration (required)
- Storage:
  - C_total (F):
  - V_cap start (V):
  - V_cap end (V):
  - V_cap limits (min enable / overvolt thresholds):
- Bus configuration:
  - OR’ing method:
  - fuse ratings:
  - precharge method:
- Conversion:
  - rails enabled:
  - load profile (constant load, duty cycle, burst schedule):
- ThermalGuardian parameters (amber/red thresholds):

## Instrumentation & calibration (required)
- Instruments used (DMM, scope, DAQ, etc.):
- Shunts:
  - shunt_ohms_mod{i} (measured):
  - shunt_ohms_cap (measured):
- Voltage divider ratios (measured):
- ADC reference, resolution:
- Thermal sensor type and placement:

Attach:
- `calibration.json` (or equivalent)
- photos of setup (recommended)

## Data files (required)
- raw log CSV path:
- any additional logs:
- plots (optional):

## Energy reconciliation (required)
Compute using `docs/04_ENERGY_TRUTH_PROTOCOL.md`.

- E_in (sum of modules):
- ΔE_cap (cap energy delta or integrated V*I):
- E_out (sum of rails):
- E_loss (E_in - ΔE_cap - E_out):

Explain losses:
- conversion efficiency estimate:
- OR’ing/rectifier loss:
- wiring loss:
- leakage/ESR heating:
- controller overhead:

## Thermal behavior (required)
- peak t_conv_c:
- peak t_cap_c:
- derating events observed:
- shutdown events observed:
- notes:

## Pass/Fail against success metrics
Reference `docs/03_SUCCESS_METRICS.md`.
- M1 Energy accounting closes: PASS/FAIL
- M2 Stable rails: PASS/FAIL/N/A
- M3 Thermal safety enforced: PASS/FAIL
- M4 No backfeed / no fighting: PASS/FAIL
- M5 Reproducibility package complete: PASS/FAIL
- M6 Honest scope maintained: PASS/FAIL

## Notes / next actions
- What worked:
- What failed:
- Proposed changes:
