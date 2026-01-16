# File: docs/modules/MODULE_A_EFIELD.md
# IX-Legacy — Module A: E-Field Harvester (Capacitive Coupling) (v0)

## 0) Purpose
Module A harvests energy from **time-varying electric fields** present in the environment
(e.g., around energized AC infrastructure) using **capacitive coupling**.

This module targets **low-power trickle** contributions and is most valuable when:
- vibration is weak/unavailable,
- thermal gradients are weak/unavailable,
- but energized wiring/equipment is nearby.

## 1) Physics basis (what is real)
A time-varying electric field can induce displacement currents in a conductor (an “electrode”)
that is capacitively coupled to the field source. With appropriate rectification and storage,
some of that energy can be harvested.

Key constraints:
- The source is typically **high voltage / extremely low current**.
- Output depends strongly on geometry, distance, shielding, frequency, and environment.
- The system must remain **non-contact** to stay safe and legally sane.

## 2) Safety boundaries (non-negotiable)
- **No galvanic contact** to mains conductors or infrastructure.
- Module must be designed so any exposed electrode is current-limited and cannot deliver
  hazardous current (high impedance + protective network).
- Evaluation must be performed only in safe, controlled environments with appropriate
  electrical safety practices. This repository does not provide “how to harvest from mains”
  instructions.

## 3) Functional block diagram
[E-field Electrode] ── C_couple ──► [HV / High-Z Front End]
                              └──► [Protection: clamp + bleed + limit]
                                       │
                                       ▼
                             [Rectification / Charge Pump]
                                       │
                                       ▼
                              [Local Buffer (Cbuf)]
                                       │
                                       ▼
                          [Impedance Control / MPPT (optional)]
                                       │
                                       ▼
                       [OR’ing + Fuse] ──► Common Harvest Bus

## 4) Core components (classes)
### 4.1 Electrode geometry (choose per enclosure)
- Single large-area electrode referenced to device “return” (floating return)
- Dual-electrode differential pickup (two electrodes with symmetric exposure)

Design goal:
- maximize coupling capacitance to the ambient field,
- while keeping touch-safe surfaces and predictable insulation.

### 4.2 Protection / conditioning (required)
- Bleed path (high value resistor) to prevent charge accumulation when disconnected
- Voltage limiting/clamping to protect downstream electronics
- Input current limiting (design for inherently tiny current)

### 4.3 Rectification strategy
Because signals can be high voltage but low energy:
- Favor **low-leakage** rectification and storage
- Avoid heavy diode losses where possible
- Consider multi-stage charge pump only if validated by measurement (otherwise it can increase losses)

### 4.4 Local buffer
A small local capacitor (Cbuf) can:
- smooth intermittent coupling,
- provide a stable boundary for measurement,
- prevent the module from “fighting” the common bus at very low power.

## 5) Electrical interface to IX-Legacy bus
### Required
- V_modA: module DC output voltage into OR’ing
- I_modA: module current into bus (positive into bus)
- EN_A (optional): module enable line if active circuitry present

### Output requirements
- Must not backfeed (bus-to-module reverse current prevented by OR’ing)
- Must tolerate bus voltage range without damage (or include additional isolation)

## 6) Test & verification (what we must prove)
Module A is considered “working” only when logs show:
- positive net energy delivered into storage over a defined window,
- no backfeed,
- stable behavior across connection/disconnection.

### Measurement boundaries (required)
- Measure at module boundary before OR’ing:
  - v_modA_v, i_modA_a
- Also log storage boundary:
  - v_cap_v, i_cap_a

### “No-deception” rule
If any active circuitry is powered by the device’s storage,
that consumption must be measured as part of system output energy.

## 7) Expected performance posture (honest scope)
- Treat Module A as a **trickle contributor**.
- Environment dominates results: shielding, distance, frequency, and geometry matter more
  than “clever circuitry.”
- IX-Legacy must present results as a function of measured environment conditions, not as a universal claim.

## 8) Failure modes to design against
- Electrostatic accumulation causing unexpected spikes → mitigate with bleed + clamps
- Leakage paths dominating harvested energy → choose low-leakage components and clean layout
- Backfeed from bus raising module node → OR’ing + isolation
- Human touch coupling changing behavior → enclosure design and guard strategy

## 9) Gate to graduate from “spec” to “validated”
To graduate Module A, we must produce:
- a run log per `docs/04_ENERGY_TRUTH_PROTOCOL.md`
- a reconciliation report where E_in(Module A) is demonstrably > 0
- a backfeed test proving i_modA never goes negative beyond noise bounds
