# File: hardware/modules/MODULE_B_VIBRATION_HARDWARE_NOTES.md
# IX-Legacy — Module B Hardware Notes (v1)

## 1) Tube count philosophy (baseline)
Do not assume “more tubes” equals more power.
Capture is limited by available motion energy and mechanical coupling.

Baseline recommendation for v0/v1 prototypes:
- Start with 36–60 tubes total (3–5 rings), instrument per ring, and scale only if logs prove benefit.

## 2) Ring construction
- Build rings as serviceable subassemblies (swap a ring without tearing down the entire device)
- Keep coil-to-rectifier wiring short and low resistance
- Provide strain relief; vibration kills weak solder joints

## 3) Rectification implementation posture
- Prefer active/synchronous rectification for low-voltage coil outputs
- If Schottky is used, document:
  - expected conduction loss (I * Vf) across operating range
  - leakage impact at low harvested power
  - measured thermal rise at rectifier

Non-negotiable:
- Rectification choice must be justified by measurement, not “looks fine.”

## 4) OR’ing and fusing
- Each ring must have:
  - its own ideal-OR (or equivalent) into the bus
  - its own fuse sized to wiring and credible fault current
- Do not share fuses across rings.

## 5) Mechanical notes
- Use non-magnetic structural materials near magnet stroke paths where practical
- Provide guides to avoid magnet scraping (friction kills output)
- Include mechanical stops for shock events
- Balance mass distribution to avoid self-damping and unpredictable modes
