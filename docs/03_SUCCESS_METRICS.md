# File: docs/03_SUCCESS_METRICS.md
# IX-Legacy — Success Metrics (v0)

## M1 — Energy accounting closes
- For a defined test window, logged:
  - Sum(E_in from modules) ≈ ΔE_supercap + Sum(E_out to loads) + losses
- “Losses” must be explainable (converter efficiency, diode/OR losses, wiring, leakage, heat rise).

## M2 — Stable rails under defined conditions
- Under a defined load profile, 5V/12V rails remain within tolerance *while buffer allows*.
- On buffer depletion, the system load-sheds cleanly (no oscillation / no brownout chatter).

## M3 — Thermal safety enforced
- Converter and storage temps remain below defined limits in steady operation.
- Derating engages before runaway; hard shutdown triggers at critical limits.

## M4 — No backfeed / no fighting
- Disconnecting one module does not cause reverse current into it.
- Adding a module does not collapse the bus (precharge verified).

## M5 — Reproducibility
- A third party with common lab instruments can reproduce the test and obtain comparable results
  within defined tolerances for the same environment and setup.

## M6 — Honest scope
- Reported output is explicitly tied to the environment (vibration profile, ΔT, lighting, E-field presence, RF density).
- No “ambient” claim without stating the measured environment bounds.
