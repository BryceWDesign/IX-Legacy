# File: docs/09_LOW_LOSS_RECTIFICATION.md
# IX-Legacy — Low-Loss Rectification Notes (v0)

## 0) Why this exists
At small harvested power levels, rectification losses can consume most of what you capture.
This doc defines acceptable rectification choices and how we justify them.

## 1) The problem
Classic silicon bridges are convenient but often have too much forward drop and loss for
low-voltage, low-power harvesters. If a harvester produces small RMS voltage/current, a
large fraction of energy can disappear across the rectifier.

## 2) Acceptable rectification families (IX-Legacy posture)
### A) Synchronous / active rectification (preferred)
- MOSFET-based “ideal bridge” behavior at AC → DC boundaries
- Best when harvested AC amplitude is low and every milliwatt matters

### B) Schottky bridge (fallback)
- Use only when:
  - the expected harvested voltage/current regime makes losses acceptable, AND
  - leakage is not dominating the energy flow, AND
  - measured logs confirm net benefit

### C) Converter-integrated rectification (optional)
- An AC-DC or AC-conditioned stage per ring can be acceptable only if:
  - the converter overhead is explicitly measured and included in reconciliation, AND
  - it does not cause false “harvest” readings (Energy Truth boundaries must surround it)

## 3) What we must measure to justify any choice
For the selected rectification path, log:
- input AC characteristics (at least RMS or representative time samples if available)
- rectified DC output (V/I) at ring boundary
- thermal rise at rectifier/OR components
- system reconciliation: E_in → ΔE_cap + E_out + losses

If the system cannot close the energy accounting, the rectification choice is not validated.

## 4) Repo rule (locked)
No “measured output” claim is allowed unless rectification losses are bounded by real logs.
