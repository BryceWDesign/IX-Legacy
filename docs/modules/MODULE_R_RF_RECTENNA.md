# File: docs/modules/MODULE_R_RF_RECTENNA.md
# IX-Legacy — Module R (Optional): RF Rectenna Tile Array (v0)

## 0) Purpose
Module R harvests energy from **ambient radio-frequency (RF) electromagnetic fields**
using rectifying antennas (“rectennas”).

This module is optional because:
- ambient RF energy density is often **very low**,
- output is typically **µW to mW** unless very near strong transmitters,
- performance is extremely environment-dependent.

Module R is still valuable as:
- a “bonus trickle” input,
- an R&D measurement module (quantifying RF density in real environments),
- a wideband capture skin when integrated into enclosure tiles.

## 1) What’s real (and what isn’t)
Real:
- Antennas can capture RF power; rectifiers can convert it to DC.
- Arrays can increase effective capture area and broaden coverage.
- Wideband designs can harvest across multiple bands.

Not real:
- “Free” watts from typical indoor ambient RF without proximity to strong sources.
- Any claim of high-power RF harvesting without explicitly measured field conditions.

## 2) Functional block diagram
[Wideband Antenna Element] → [Matching Network] → [Rectifier] → [Local Cbuf]
                                                │
                                                ▼
                                   [Tile combiner (DC)]
                                                │
                                                ▼
                             [OR’ing + Fuse] → Common Harvest Bus

## 3) Tile strategy (recommended)
Instead of wiring 99 individual antennas directly into one bus:
- build “tiles” that contain a small number of elements (e.g., 9–16 per tile),
- each tile rectifies locally and produces a DC output,
- tiles OR together at the bus.

Why:
- reduces inter-element “fighting”
- keeps rectifier losses local
- improves serviceability
- enables per-tile measurement and swapping

## 4) Element strategy (v0 posture)
### 4.1 Wideband / multiband elements
Goal: cover common ambient bands (cellular, Wi-Fi, broadcast, etc.) without brittle tuning.

Allowed design families:
- wideband monopoles/patches sized for enclosure
- spiral/fractal-style elements (for multiband compactness)
- segmented arrays with different element sizes to span bands

Rule: any element choice must be validated with measurement; do not claim band coverage without data.

### 4.2 Polarization and orientation
Ambient RF polarization varies. Use:
- mixed orientations across tiles
- at least two polarization strategies across the enclosure skin
This increases capture probability in unknown environments.

## 5) Rectification (critical loss point)
Rectifiers dominate performance at low input power.
Guiding rules:
- minimize leakage
- minimize forward drop
- avoid designs that only work above a high RF input threshold
- use local buffering so the rectifier sees a more stable load

Important:
If the rectifier/control electronics require power, that consumption must be captured in energy accounting.

## 6) Electrical interface to IX-Legacy bus
Required:
- v_modR_v, i_modR_a measured pre-OR at the module boundary
Recommended:
- per-tile v_tile_j, i_tile_j for tuning and comparative tests

Module must:
- never backfeed (OR’ing required)
- tolerate bus voltage range or include isolation

## 7) Test & verification (required)
Because RF is environment-driven, reporting must include:
- location description (indoor/outdoor, near transmitters or not)
- antenna/tiles used and placement
- measurement window duration

Pass criteria:
- net positive energy delivered into storage for the window
- stable behavior (no oscillation, no backfeed)

## 8) Honest expectation posture (locked)
Module R is reported as:
- “trickle contributor” unless demonstrated otherwise in a specific measured environment
- always tied to the environment
- never used as the sole justification for medium/high power claims
