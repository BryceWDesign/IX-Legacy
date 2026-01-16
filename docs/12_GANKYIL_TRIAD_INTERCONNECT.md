# File: docs/12_GANKYIL_TRIAD_INTERCONNECT.md
# IX-Legacy — Gankyil Triad Interconnect (v0)

## 0) Purpose
Define how three identical IX-Legacy units connect and behave as **one system** while:
- preventing backfeed between units,
- preventing inrush damage when sharing storage/buses,
- enabling role-based control (Buffer/Conversion/Sense),
- maintaining Energy Truth accounting boundaries.

## 1) Physical layout (Gankyil constraint)
Three units are placed as a three-lobe formation (each lobe adjacent to the other two).
Geometry is used for:
- symmetric wiring lengths,
- predictable mechanical mounting,
- repeatable coupling surfaces for modules (if skin tiles/electrodes used).

Geometry is not treated as an energy source.

## 2) Electrical interconnect topology (authoritative)
Each unit exports a **Local Harvest Bus** into a shared **Backbone Bus**.

Per-unit connection to Backbone MUST include:
- Ideal-diode OR’ing (prevents reverse current from Backbone into a unit)
- Fuse/breaker per unit (fault containment)
- Controlled precharge path (prevents inrush into shared capacitance)

High-level:
[Unit A Local Bus] -- OR_A -- FUSE_A -- PRECHARGE_A/BYPASS_A --> [Backbone Bus]
[Unit B Local Bus] -- OR_B -- FUSE_B -- PRECHARGE_B/BYPASS_B --> [Backbone Bus]
[Unit C Local Bus] -- OR_C -- FUSE_C -- PRECHARGE_C/BYPASS_C --> [Backbone Bus]

Backbone Bus then interfaces to the system’s Tri-Core Router functions:
- storage, conversion, sensing, dump path.

## 3) Storage strategy (choose one; document which)
### Option S1: Shared Storage (recommended for “one device” behavior)
- One designated Buffer Master hosts the primary supercap bank.
- Other units contribute harvested energy to the Backbone; the Buffer Master manages V_cap, dump, etc.
- Benefits: simplest Energy Truth boundary, simplest safety, cleanest gating.

### Option S2: Distributed Storage (advanced)
- Each unit retains its own supercap bank.
- Backbone is used to share energy via controlled transfer rules.
- Requires additional transfer logic and stricter precharge/OR’ing discipline.
- Only allowed after shared-storage version is validated.

IX-Legacy v0 uses S1.

## 4) Role assignment (Borromean in triad form)
Triad must ensure all three roles exist:

A) Buffer Master
- owns V_cap sensing, I_cap sensing, balancing, dump path
- is the authoritative “safe discharge” controller
- can isolate the Backbone via a contactor (optional) in fault events

B) Conversion Master
- owns regulated rails and load shedding
- enables/disables rails based on Buffer Master’s V_cap + Sense Master’s fault/thermal status

C) Sense Master
- owns “Energy Truth” reconciliation boundary oversight
- logs module inputs (as available), bus conditions, temperatures, and faults
- arbitrates faults and provides “go/no-go” state to Conversion Master

Roles can be fixed (by configuration) or elected at boot (advanced).
v0 assumes fixed roles by build-time config.

## 5) Control and telemetry interconnect
Triad units must share a low-power control link:
- RS-485 or CAN recommended (robust in noisy environments)
- Minimum message set:
  - V_cap, I_cap, T_cap (from Buffer Master)
  - T_conv, rail state (from Conversion Master)
  - Fault flags and derate factor (from Sense Master)
  - Heartbeat + role id

If control link fails:
- Conversion Master must fail-safe (rails OFF or load-shed based on last safe state).
- Buffer Master retains dump safety locally.

## 6) Precharge sequencing (non-negotiable)
When connecting a unit to the Backbone:
1) Close PRECHARGE path (resistor) and monitor ΔV between unit local bus and Backbone.
2) Only when ΔV < threshold for dwell time, close BYPASS (main path).
3) Open PRECHARGE.
4) Begin normal operation.

Timeout => isolate unit and latch PRECHARGE_TIMEOUT fault.

## 7) Fault isolation rules
- Any unit detecting reverse current at its OR boundary must isolate and latch fault.
- Any unit exceeding thermal critical must disable its contribution and report fault.
- Backbone overvoltage triggers Buffer Master dump path and may command others to isolate.

Fuses/breakers are last-resort containment; firmware must try to isolate before catastrophic fault.

## 8) Measurement boundaries for Energy Truth (triad)
At minimum log:
- Per-unit module boundaries (when instrumented): v_mod_i, i_mod_i
- Backbone: V_backbone (recommended), I_backbone (optional but helpful)
- Storage boundary at Buffer Master: V_cap, I_cap
- Rails boundary at Conversion Master: V_rail, I_rail

Triad “proof” requires reconciliation:
E_in_total ≈ ΔE_cap + E_out + losses

## 9) Validation gates (triad-specific)
Triad interconnect is considered validated only if:
- Hot-plug test: connecting/disconnecting a unit does not collapse the Backbone (precharge works)
- Backfeed test: no reverse current into a disconnected unit
- Fault test: one unit fault does not take down others (fuse isolation + OR’ing behavior)
- Energy Truth reconciliation still closes with triad connected
