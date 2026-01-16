# File: hardware/modules/MODULE_B_VIBRATION_HARDWARE_NOTES.md
# IX-Legacy — Module B Hardware Notes (v0)

## 1) Tube count philosophy (baseline)
Do not assume “more tubes” equals more power.
Power capture is limited by available motion energy and mechanical coupling.

Baseline recommendation for v0 prototypes:
- Start with 36–60 tubes total (3–5 rings) depending on enclosure size.
- Use per-ring buffering + measurement and scale only after logs prove benefit.

## 2) Mechanical notes
- Use non-magnetic structural materials near magnet stroke paths where practical
- Provide guides to avoid magnet scraping (friction kills output)
- Include service access for tube replacement
- Balance mass distribution to avoid self-damping

## 3) Electrical notes
- Short, thick conductors from coil to rectification reduce resistive loss
- Use shielding/grounding practices that do not create new leakage paths
- Keep high-impedance electret nodes physically isolated if used

## 4) Thermal notes
- Rectifiers and OR’ing elements are the first thermal hotspots
- Instrument these points early; do not “assume they are fine”
