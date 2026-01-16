# File: docs/11_TRIOSTRUT_NODES.md
# IX-Legacy — Triostrut Nodes (Controlled Points) (v0)

## 0) Purpose
A “Triostrut Node” in IX-Legacy is not mystical and not an energy source.
It is an **engineered convergence point** used to make behavior repeatable and auditable:

- **Electrical:** a deliberate junction for combining, sensing, and protecting energy flow
- **Mechanical:** a rigid mounting/strain-relief hub that survives vibration and handling
- **Field-control (optional):** a controlled geometry where you *intend* gradients to peak
  (within safe, non-hazardous bounds) so coupling/collection happens predictably

Think of it like a Tesla coil breakout tip conceptually: **shape the gradients so the system
chooses your node instead of random edges**, but without implying net energy creation.

## 1) Where Triostruts belong in IX-Legacy
Triostrut Nodes are allowed in four places:

### T1) Measurement Nodes (preferred)
- Place shunts, sense taps, and calibration points at a mechanically stable tri-node
- This reduces measurement drift caused by vibration, flex, and contact resistance changes

### T2) Combiner Nodes (module/ring aggregation)
- A tri-node is a clean place to combine:
  - (Ring DC) + (Ring DC) + (Ring DC) into one “ring-group” feed into the bus
- If OR’ing is used, Triostrut is where OR devices and fusing can be physically organized
  with consistent wiring lengths and clear boundaries.

### T3) Safety Nodes (dump/load and service discharge)
- A tri-node is a good anchor for:
  - dump load connection
  - service discharge connection
  - “safe measurement” points for verifying Vcap is actually discharged

### T4) Field-coupling Node (Module A only; optional and conservative)
- If using E-field coupling electrodes/guards, a tri-node can define a controlled connection
  between the electrode, guard/shield, and the high-impedance front end.
- This is about **repeatability and leakage control**, not generating power.

## 2) The “two into one, one to center” interpretation (Triostrut version)
- Two (or three) sources feed a **tri-node combiner**, but ONLY through OR’ing that prevents
  source-fighting.
- The combiner outputs one controlled feed into the **Tri-Core Router** center hub.
- The center hub decides when/how energy is released to loads (conversion gating).

## 3) Non-negotiable electrical rules for Triostrut Nodes
N1) A Triostrut Node must never violate bus invariants:
- no backfeed
- precharge enforced
- fusing present
- dump path available

N2) Any tri-node that merges sources MUST merge after:
- rectification (for AC sources), and
- local buffering where appropriate,
and must merge through OR’ing so no node can drive another backwards.

N3) Any tri-node used for sensing MUST:
- have a defined Kelvin path if it is a shunt measurement point
- be physically protected from flexing that changes resistance

## 4) Mechanical rules (so it doesn’t become a failure point)
M1) Triostrut is a **strain-relief hub**:
- all wires entering must be strain relieved
- vibration-rated connectors preferred
- no “hanging” heavy components off solder joints

M2) Symmetry matters:
- symmetric routing reduces unintended coupling and measurement bias
- consistent wire lengths reduce parasitic imbalance between rings/modules

## 5) What Triostruts cannot do
- They cannot create net energy.
- They cannot “focus” energy into existence.
- They can only:
  - reduce losses,
  - stabilize coupling,
  - stabilize routing,
  - and make measurement repeatable.

## 6) Validation gate (must be proven)
A Triostrut Node is “helpful” only if it measurably improves at least one:
- reduced run-to-run variance (repeatability)
- reduced unexplained losses (leakage/connection heating)
- improved measurement stability (less drift/noise)
while maintaining:
- no backfeed,
- safe precharge,
- thermal limits.

Proof must follow `docs/04_ENERGY_TRUTH_PROTOCOL.md`.
