# File: docs/02_REQUIREMENTS.md
# IX-Legacy — Requirements (v0)

## R0 — Integrity / Claims
R0.1 Any performance claim in README must link to a reproducible test log.
R0.2 Any unverified idea must be clearly labeled “Hypothesis” until validated.

## R1 — Electrical Safety
R1.1 Per-module isolation: each harvester module must have OR’ing to prevent backfeed.
R1.2 Per-module protection: each module must have a fuse (or resettable fuse) sized to safe limits.
R1.3 Inrush control: connecting/disconnecting large capacitances must use a precharge path.
R1.4 Safe discharge: a controllable dump path must exist for the supercap bank.
R1.5 Overvoltage: storage must be protected against exceeding max rated V.

## R2 — Measurement / “Energy Truth”
R2.1 Must measure V/I per harvester module at its input to the common bus.
R2.2 Must measure storage V/I into/out of the supercap bank.
R2.3 Must measure output rail V/I to loads.
R2.4 Logs must include timestamps and calibration constants.
R2.5 The system must support energy reconciliation (input energy vs stored vs delivered).

## R3 — Thermal Safety
R3.1 Must monitor temperature at conversion hotspots and near storage.
R3.2 Must derate power delivery as temperature rises (defined curve).
R3.3 Must fault and shut down on critical temperature thresholds.

## R4 — Modularity
R4.1 Harvester modules must be swappable without redesigning the backbone.
R4.2 Adding/removing a module must not destabilize the bus (precharge + isolation + sane defaults).

## R5 — Operational States
R5.1 Must implement a documented state machine: safe start, harvest-only, charge, regulate, load-shed, fault.
R5.2 Faults must be latched where appropriate and require explicit recovery action.

## R6 — Non-weapon / Safety Scope
R6.1 Repository must not include design content intended to cause harm.
R6.2 Testing must be done in safe, legal environments with appropriate PPE and compliance as applicable.
