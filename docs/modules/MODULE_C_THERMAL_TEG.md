# File: docs/modules/MODULE_C_THERMAL_TEG.md
# IX-Legacy — Module C: Thermal Gradient Harvester (TEG) (v0)

## 0) Purpose
Module C harvests energy from **real thermal gradients (ΔT)** using thermoelectric generators (TEGs).
This is the best path to meaningful continuous power *when* a real heat flow exists.

## 1) Physics basis (what is real)
TEGs convert a temperature gradient into voltage (Seebeck effect).
Key constraints:
- Output power depends on ΔT, thermal coupling, and load matching.
- Good mechanical clamping and heat sinking matter more than clever electronics.
- A TEG is not a heater/cooler by default; it’s a converter that needs heat flow.

## 2) Functional block diagram
[Hot-side interface] ─► [TEG] ─► [Cold-side interface]
                             │
                             ▼
                     [Ultra-low-V step-up]
                     (as required by ΔT and TEG selection)
                             │
                             ▼
                [Impedance control / MPPT (optional)]
                             │
                             ▼
              [OR’ing + Fuse] ─► Common Harvest Bus

## 3) Thermal interfaces (most important part)
### 3.1 Hot-side sources (examples)
- engine bay components, radiator pipes, exhaust-adjacent heat (safe distance)
- industrial process pipes
- sun-heated plates (outdoor)
- electronics heatsinks (only if it doesn’t raise hotspot temps)

### 3.2 Cold-side sinks (examples)
- ambient air heatsink + airflow
- chassis thermal mass
- dedicated finned heatsink
- forced convection (fan) if energy budget allows

Rule: A TEG only performs if heat can move from hot to cold; both sides must be engineered.

## 4) Electrical interface to IX-Legacy bus
Required:
- v_modC_v, i_modC_a at module boundary (pre-OR)
- t_hot_c and t_cold_c (recommended for credible reporting)
Optional:
- ΔT = t_hot_c - t_cold_c computed and logged

## 5) Impedance matching & conversion
TEGs often produce low voltage at small ΔT.
Module C may require:
- a dedicated ultra-low-voltage step-up stage
- a simple MPPT-like control to present the right effective load

Important:
- Do not claim MPPT performance without measurement.
- Conversion overhead must be included in energy accounting.

## 6) Safety boundaries
- Do not mount TEGs where failure could create burns, fires, or hazardous contact.
- Clamp forces and insulation must be appropriate for temperature range.
- If mounting near equipment, respect facility safety rules and regulations.

## 7) Test & verification (required)
### 7.1 Minimum environment description
- hot-side temperature (t_hot_c)
- cold-side temperature (t_cold_c)
- mounting method and contact materials
- airflow conditions

### 7.2 Measurement boundaries (required)
- v_modC_v, i_modC_a
- v_cap_v, i_cap_a
- rail outputs if conversion enabled

### 7.3 Pass criteria
- Net positive energy delivered into storage for a defined ΔT window
- Stable operation without thermal runaway in conversion electronics
- Report performance as a function of ΔT (not as a universal claim)

## 8) Failure modes to design against
- Poor clamping/contact → low ΔT across the TEG (most common failure)
- Converter overhead dominates at low ΔT → measure overhead and gate enable
- TEG cracking under thermal stress → mount with compliant interface materials
- Adding TEG increases hotspot temps (if mounted on heatsink) → avoid or redesign
