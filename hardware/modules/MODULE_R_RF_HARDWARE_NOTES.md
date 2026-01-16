# File: hardware/modules/MODULE_R_RF_HARDWARE_NOTES.md
# IX-Legacy — Module R Hardware Notes (v0)

## 1) Physical integration
- Treat RF tiles as a “skin” layer that can be swapped without opening the core
- Use consistent connectors per tile for testability
- Keep rectifier circuits shielded from noisy switching converters (noise can swamp µW signals)

## 2) Combining strategy (do this, not the messy version)
- Combine at DC after local rectification + buffer
- Do not parallel raw antenna elements into a shared rectifier bus (performance collapses)

## 3) Measurement discipline
- Measure at the tile boundary first (per tile)
- Only then aggregate tiles and measure module boundary
- If output is near noise floor, extend test time and average correctly; do not “eyeball it”
