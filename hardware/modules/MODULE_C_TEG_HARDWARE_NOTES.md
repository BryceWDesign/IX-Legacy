# File: hardware/modules/MODULE_C_TEG_HARDWARE_NOTES.md
# IX-Legacy — Module C Hardware Notes (v0)

## 1) Mechanical mounting
- Flatness matters: ensure surfaces are reasonably flat
- Use appropriate thermal interface material (TIM) for the temperature range
- Use controlled clamping pressure (springs or torque spec) to avoid cracking the TEG

## 2) Instrumentation
- Always instrument both sides:
  - hot-side temp near the contact point
  - cold-side temp near the contact point
- Log ΔT; it is the single most important explanatory variable

## 3) Cold-side design
- “Cold side” must be able to reject heat.
- If the cold side warms up, ΔT collapses and output collapses.

## 4) Electrical routing
- Keep TEG leads short to reduce resistive losses
- Route away from noisy switching nodes when possible
- Protect against accidental short circuits (TEGs can source significant current at high ΔT)

## 5) Do-not-do list
- Don’t mount a TEG on a converter heatsink if it raises converter temperature beyond safe limits
- Don’t claim watts without reporting ΔT and mounting details
