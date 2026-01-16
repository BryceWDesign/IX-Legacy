# File: docs/05_COMMON_BUS_SPEC.md
# IX-Legacy — Common Bus Specification (v0)

## 0) Purpose
Define the electrical “spine” that all harvester modules and all triad nodes connect to.
This bus is designed to:
- prevent backfeed between sources,
- prevent inrush damage when connecting capacitance,
- enforce safe discharge,
- provide a clean boundary for energy accounting.

## 1) Canonical topology (single device)
Each harvester module connects to the Common Harvest Bus through:
- an OR’ing element (ideal-diode controller + MOSFET, or Schottky as a fallback),
- a fuse (or resettable fuse) per module,
- optional module-side buffer capacitor if needed.

Common Harvest Bus then feeds:
- Storage branch (supercap bank) through a controlled precharge path,
- Conversion branch (regulators) through enable/derating rules.

## 2) Canonical topology (Gankyil triad)
Three identical IX-Legacy units combine via a Backbone Bus:
- Each unit’s local bus connects to the Backbone through:
  - OR’ing (prevents backfeeding into a unit),
  - fuse/breaker per unit,
  - precharge before closing main contactor to the Backbone (if contactor is used).

A single authoritative “Bus Safety Module” may be used:
- master dump load,
- master contactor (optional),
- master measurement boundary (bus V/I).

## 3) Electrical invariants (must always hold)
B1) No backfeed: current must not flow from bus → module outputs.
B2) Inrush controlled: no direct hot-plug of large capacitances without precharge.
B3) Safe discharge exists: supercap bank must be able to discharge to a known safe level.
B4) Fault isolation: a faulted module must be isolatable without taking down the bus.

## 4) OR’ing strategy (no-backfeed)
### Preferred: “ideal diode” MOSFET OR’ing
- Lowest practical loss at low voltages/currents
- Enables clean combining of weak harvesters
- Prevents module-to-module fighting

### Acceptable fallback: Schottky diode OR’ing
- Simpler but wastes energy as heat (often unacceptable for small harvesters)
- Use only for early prototypes or very low currents

Rule: Any module that cannot tolerate reverse bias must *still* be isolated by the bus OR’ing.

## 5) Fuse strategy (fault containment)
Each module input must include:
- a series fuse (or resettable PTC) sized to protect wiring and module components.
- triad node interconnect must include a fuse/breaker per node.

Rule: fuses are selected based on wiring gauge, connector rating, and maximum credible fault current.

## 6) Precharge strategy (capacitance management)
Precharge is required when connecting:
- supercap banks,
- large module buffer capacitors,
- triad node backbones.

### 6.1 Simple precharge (prototype)
- series resistor + MOSFET/relay bypass:
  1) close precharge path (resistor) until bus and cap voltages converge
  2) close main path (bypass) after convergence
  3) open precharge path

### 6.2 Managed precharge (recommended)
- controller monitors ΔV = |V_bus - V_cap|
- only closes main bypass when ΔV < threshold for a minimum dwell time
- aborts if precharge timeout occurs (indicates short or abnormal load)

Rule: precharge must be enforced in firmware state machine and/or hardwired logic.

## 7) Dump / discharge path (safety)
Supercap bank must have:
- a controllable dump load (resistor bank or equivalent),
- a “service discharge” procedure in docs.

Dump path uses:
- a switch element (MOSFET/relay) rated for the bus voltage,
- a resistor value that sets a safe discharge time constant,
- thermal consideration for resistor dissipation.

Rule: Dump path must be usable even if firmware is offline (service-mode or manual procedure).

## 8) Measurement boundaries for Energy Truth
Required measurement points at the bus:
- V_bus (post-OR’ing)
- V_cap and I_cap at storage boundary
- optional I_bus for total bus current (recommended for reconciliation)

Per module:
- V_mod_i and I_mod_i prior to OR’ing into bus (canonical)

Triad:
- V_backbone and per-node I_node recommended

## 9) Fault states (bus-level)
F0 — Normal: bus within expected range, precharge complete, no thermal or overcurrent faults.
F1 — Precharge timeout: indicates short/abnormal load; latch fault and isolate.
F2 — Overvoltage: isolate sources and/or route to dump path; latch if persistent.
F3 — Overcurrent: blow fuse or trip protection; isolate affected branch; latch.
F4 — Thermal critical: disable conversion/load and engage derating or shutdown; latch.
F5 — Reverse current detected: indicates OR’ing failure; isolate and latch.

## 10) “No deception” rule
The bus spec forbids any topology where a converter can draw from storage and make it appear
as if a harvester is sourcing power unless the measurement boundaries explicitly capture it.
All claims must be reconciled via `docs/04_ENERGY_TRUTH_PROTOCOL.md`.
