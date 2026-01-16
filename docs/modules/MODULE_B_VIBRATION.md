# File: docs/modules/MODULE_B_VIBRATION.md
# IX-Legacy — Module B: Vibration / Kinetic Harvester (v0)

## 0) Purpose
Module B converts external motion/vibration into electrical energy.
This module is the “workhorse” in environments where vibration is continuously present
(motors, pumps, vehicles, handheld motion).

## 1) Physics basis (what is real)
Vibration harvesters are real and fall into several families:
- Electromagnetic (moving magnet through coil / moving coil in field)
- Piezoelectric (strain generates charge)
- Electrostatic / electret (variable capacitor; electret provides a permanent bias)
- Triboelectric (contact/separation charge transfer)

IX-Legacy v0 prioritizes **electromagnetic** + optional **electret** because they are robust,
serviceable, and compatible with supercap buffering.

Key constraint:
- Output power scales with the environment’s acceleration spectrum and mechanical design.
- If the unit is stationary in a low-vibration environment, power → near zero.

## 2) Sub-architectures supported (choose one or mix, but validate)
### B1) Linear electromagnetic tube (“shake flashlight” class)
- Magnet mass moves through coil, generating AC
- Rectify → buffer → bus

### B2) Tuned resonant linear alternator (preferred upgrade path)
- Spring-mass system tuned to dominant vibration frequency band
- Increased stroke and energy capture at resonance
- Requires mechanical stops and fatigue-aware design

### B3) Electret-based electrostatic harvester (optional parallel path)
- Variable capacitor + electret film yields high voltage / very small current
- Needs careful rectification and very low leakage
- Useful for broadening frequency response and “static-like” behavior without external HV

## 3) What we change vs. ZeroCell (critical improvements)
B3.1 Stop using heavy silicon bridge rectifiers for low-power AC sources
- They waste harvested energy as forward-drop heat.

B3.2 Use low-loss rectification + per-string buffering
- Each cluster (“ring”) should have its own rectification and buffer capacitor
  so clusters don’t fight each other through the common bus.

B3.3 Combine at DC through ideal-diode OR’ing
- Prevents reverse currents and inter-string energy cancellation.

B3.4 Tune the mechanics instead of brute-forcing tube count
- More tubes without sufficient excitation dilutes motion and increases losses.

## 4) Canonical “ring” topology (recommended for tube arrays)
Group tubes into rings/strings:

[Tubes in ring] → [Ring rectification (low-loss)] → [Ring buffer Cbuf] → [OR + Fuse] → Bus

Benefits:
- minimizes cross-coupling losses
- isolates faults
- allows per-ring measurement and optimization

## 5) Electrical interface to IX-Legacy bus
Required signals:
- v_modB_v, i_modB_a at module boundary (pre-OR’ing)
- optional per-ring signals (v_ring_j, i_ring_j) if instrumented
- optional t_modB_c (rectifier hotspot)

Module must:
- tolerate bus voltage range or include isolation
- never backfeed (OR’ing required)

## 6) Mechanical architecture (enclosure-level, not “magic”)
### 6.1 Cylinder pack (baseline)
- Tubes distributed evenly around perimeter
- Internal elastomer isolation to shape a predictable “shake mode”
- Mechanical stops to protect magnets/coils under shock

### 6.2 Resonant mounts (upgrade)
- A spring-mass mount tuned to known vibration frequencies
- Can be implemented per-ring to create multiple resonant peaks (broadband capture)

Rule: any resonance design must be validated for fatigue and shock survivability.

## 7) Test & verification (required)
### 7.1 Environment description
Minimum:
- qualitative vibration source description
Recommended:
- approximate dominant frequency band and acceleration amplitude

### 7.2 Measurement boundaries (required)
- v_modB_v, i_modB_a (pre-OR)
- v_cap_v, i_cap_a
- rail outputs if conversion enabled

### 7.3 Pass criteria
- Net positive energy delivered into storage over defined window
- No backfeed behavior during connect/disconnect
- Thermal rise within ThermalGuardian rules

## 8) Failure modes to design against
- Rectifier losses dominate at low voltages → use low-loss rectification
- Mechanical wear/fatigue → robust guides, stops, materials
- Coil heating at high excitation → thermal sensing and derating
- Noise coupling to measurement → filtering + correct boundary placement
