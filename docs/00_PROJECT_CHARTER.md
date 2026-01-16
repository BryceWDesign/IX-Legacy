# File: docs/00_PROJECT_CHARTER.md
# IX-Legacy — Project Charter (v0)

## 1) Objective
Develop a modular, verifiable energy-scavenging platform that can operate **batteryless** (or battery-minimal) by:
- Harvesting from **real ambient gradients** present in the deployment environment
- Buffering energy in **supercapacitors**
- Delivering stable regulated rails for intermittent loads
- Proving performance using **input/output energy accounting**

## 2) Non-goals
- No claims of “free energy,” “overunity,” or self-powering from internally generated fields.
- No weaponization or harm-enabling functionality.
- No field deployment in hazardous environments without a formal safety plan and regulatory compliance.

## 3) Design principles (locked)
- **Truth first:** Every claim must trace to measurements or be labeled as hypothesis.
- **Modularity:** Harvesters are swappable front-ends with defined electrical interfaces.
- **Safety:** Thermal derating, overcurrent protection, fuse isolation, dump load, and controlled discharge.
- **Repeatability:** A third party can reproduce the measurement procedure using commodity instruments.

## 4) Primary system blocks
A) Storage/Buffer
- Supercap bank sized to target burst profile
- Balancing + overvoltage protection
- Safe discharge (“dump path”) and service procedure

B) Conversion/Regulation
- Harvest-side conditioning (rectification/MPPT where appropriate)
- Bus regulation to target rails (5V/12V)
- Load shedding / brownout management

C) Sensing/Control
- Shunt-based current measurement
- Voltage measurement at harvester inputs, bus, and rails
- Temperature sensing at conversion hotspots and storage
- Fault state machine (safe states, latch faults, recovery rules)
- Telemetry logging format for auditability

## 5) Validation gates (must pass before README claims)
Gate 1 — Measurement integrity
- Calibrated shunts / meters and logged raw samples
- Demonstrated energy reconciliation (input → storage → output)

Gate 2 — Thermal safety
- Sustained operation within defined derating curves
- Verified fault shutdown behavior

Gate 3 — Module independence
- Harvester modules do not backfeed each other
- Hot-swap behavior controlled (precharge + ORing + fuse isolation)

## 6) Initial target class (v0)
- Low-to-medium power: trickle harvest + burst output
- Intended loads: sensing/telemetry, microcontrollers, intermittent comms, ride-through UPS-like behavior
