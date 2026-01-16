# File: docs/modules/MODULE_B_VIBRATION.md
# IX-Legacy — Module B: Vibration / Kinetic Harvester (v1)

## 0) Purpose
Module B converts external motion/vibration into electrical energy.
This module is the primary contributor when mounted to machinery/vehicles/structures with
continuous vibration.

## 1) Physics basis (what is real)
Vibration harvesters are real and fall into several families:
- Electromagnetic (moving magnet through coil / moving coil in field)
- Piezoelectric (strain generates charge)
- Electrostatic / electret (variable capacitor; electret provides permanent bias)
- Triboelectric (contact/separation charge transfer)

IX-Legacy prioritizes **electromagnetic** harvesting for robustness and serviceability, with
optional electret/piezo paths to broaden frequency response.

Key constraint:
- Output power scales with the environment’s acceleration spectrum and mechanical coupling.
- Stationary device in low vibration ⇒ near-zero output.

## 2) Design change vs. ZeroCell (the big fix)
ZeroCell’s “many tubes + generic bridge rectifiers” wastes a large fraction of harvested energy.
Module B v1 is defined around **low-loss rectification + ring strings + controlled combining**.

### 2.1 Ring-string topology (required)
Instead of parallelizing 99 tubes directly, group tubes into rings/strings:

[Tubes in Ring j] → [Low-loss Rectification j] → [Ring Buffer Cbuf j] → [Ideal-OR + Fuse] → Bus

Benefits:
- prevents strings from “fighting” each other
- isolates faults
- enables per-ring measurement and tuning
- improves efficiency at low harvested voltages

## 3) Rectification strategy (required)
Module B must not use high-drop commodity silicon bridges as the default.
Acceptable rectification families:

A) **Synchronous / active bridge rectification** (preferred)
- MOSFET-based active rectifier reduces effective forward drop
- best when coil voltage/current are low and losses matter

B) **Low-leakage Schottky bridge** (fallback)
- acceptable for early prototypes or when synchronous is not yet implemented
- must be justified with measured loss vs harvested power

C) **Per-ring DC-DC with rectification** (optional)
- ring AC → conditioned DC at an impedance setpoint
- only allowed if the converter overhead is measured and included in energy accounting

See `docs/09_LOW_LOSS_RECTIFICATION.md` for the non-negotiable posture:
rectification must be chosen based on measured harvested signal levels.

## 4) Electrical interface to IX-Legacy bus
### 4.1 Module boundary (required)
- v_modB_v, i_modB_a measured **pre-OR** at the module output boundary into the bus
- t_modB_c (recommended) at rectifier/OR hotspot

### 4.2 Per-ring boundary (strongly recommended)
For each ring j:
- v_ring{j}_v, i_ring{j}_a measured **after ring rectification** and before ring OR’ing
This is the fastest way to identify an underperforming ring and avoid scaling mistakes.

### 4.3 Backfeed rule
- No reverse current from bus → ring or bus → tube coils.
- Enforced by ideal-OR plus ring isolation; validated by the backfeed test in the protocol.

## 5) Mechanical architecture (enclosure-level)
### 5.1 Cylinder pack (baseline)
- Tubes distributed evenly around perimeter
- Internal elastomer isolation to shape a predictable “shake mode”
- Mechanical stops to protect magnets/coils under shock

### 5.2 Resonant mounts (upgrade path)
- Spring-mass tuning to the dominant vibration band
- Multiple rings may be tuned differently to broaden capture bandwidth
- Must be validated for fatigue and shock survivability

## 6) Test & verification (required)
### 6.1 Environment description
Minimum:
- qualitative vibration source description
Recommended:
- dominant frequency band and approximate acceleration

### 6.2 Measurement boundaries (required)
- per-ring or module boundary power into bus (v/i)
- storage boundary (v_cap, i_cap, t_cap)
- rails boundary if conversion enabled

### 6.3 Pass criteria
- net positive energy delivered into storage over defined window
- no backfeed during connect/disconnect events
- rectifier/OR thermal rise within ThermalGuardian rules
- reconciliation closes: E_in ≈ ΔE_cap + E_out + losses

## 7) Failure modes (design against)
- Rectifier losses dominate at low voltage → synchronous rectification or proven Schottky selection
- Coil heating at high excitation → thermal sensing and derating
- Mechanical wear/fatigue → robust guides, stops, serviceability
- Wiring resistance dominates → short/thick conductors, per-ring aggregation
