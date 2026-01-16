# File: docs/08_TRI_CORE_ROUTER.md
# IX-Legacy — Tri-Core Router (Center Hub) Specification (v0)

## 0) Purpose
Tri-Core Router is the **center hub** of IX-Legacy. It is the “single throat” that:
- combines multiple harvester inputs without backfeed or source-fighting,
- manages safe connection to storage (supercaps),
- enforces precharge and safe discharge,
- gates conversion/loads based on buffer + thermal + fault state,
- provides the authoritative measurement boundary for “Energy Truth.”

This is the “missing action” you described: **many inputs → one buffer → one controlled release**.

## 1) Borromean mapping (hard alignment)
Tri-Core Router implements the three interdependent rings:
A) **Buffer/Storage Core** (Supercap Bank + Balancing + Dump Path + Storage Health)
B) **Conversion Core** (Regulated rails, burst scheduling, load shedding, efficiency posture)
C) **Sense/Control Core** (Energy accounting, fault interlocks, ThermalGuardian enforcement)

If any core is missing or bypassed, the platform is either unsafe or unprovable.

## 2) Topology (conceptual)
Harvester Modules (A/B/C/R/…) each deliver conditioned DC to the **Common Harvest Bus**.

Each module connects through:
- OR’ing (ideal diode controller + MOSFET preferred)
- module fuse
- optional module buffer (local Cbuf)

Common Harvest Bus then interfaces to:
- Supercap Bank via **precharge + bypass**
- Conversion Stage via **enable gate** controlled by Sense/Control
- Dump Load via **service + fault** control

## 3) External interfaces (electrical)
### 3.1 Inputs (from harvesters)
For each module i:
- Power: V_mod_i, I_mod_i into the bus (measured pre-OR)
- Protection: fuse_i
- Isolation: OR_i (prevents bus → module reverse current)

### 3.2 Storage
- V_cap (required)
- I_cap (required, signed: +charge / -discharge)
- T_cap (required)
- Balancer status (recommended)

### 3.3 Conversion / Output rails
Per rail r:
- V_rail_r, I_rail_r (required if rail enabled)
- T_conv (required)

### 3.4 Service / Safety controls
- PRECHARGE_EN (controls precharge path)
- BYPASS_EN (closes main bus-to-cap bypass after precharge)
- DUMP_EN (enables dump load)
- RAILS_EN (enables conversion/rails)

All of these are permitted to be hardwired, firmware-controlled, or hybrid, but the invariants must hold.

## 4) Non-negotiable invariants
R1) **No backfeed**
- No current may flow from bus/storage back into any module output node.

R2) **No blind inrush**
- No direct connection of large capacitance to bus without precharge.

R3) **Dump path always available**
- A safe discharge path must exist for the supercap bank (service mode and/or fault mode).

R4) **Truth boundary enforced**
- The measurement points in `docs/04_ENERGY_TRUTH_PROTOCOL.md` must surround the Router so
  energy cannot “disappear” or be misattributed.

R5) **Thermal overrides performance**
- ThermalGuardian overrides rail enable and can force load-shed/shutdown.

R6) **Faults win**
- Overvoltage, reverse current, and precharge timeout latch and require explicit recovery.

## 5) “Two into one, one out” interpretation (what you’re seeing)
- “Two into one” = multiple module inputs OR into the common bus and charge the supercap bank.
- “One out” = the conversion core releases energy from the supercap bank to the rails only when allowed.
- “Center action” = precharge, gating, burst scheduling, and fault-safe discharge *all happen here*.

## 6) Toroid + Triostrut reinterpretation (physics-clean usage)
This repo does **not** treat geometry as an energy source. Geometry is used for:
- **Field shaping** (reducing stray electric-field loss and forcing discharge/collection to known points)
- **Routing stability** (repeatable coupling surfaces, repeatable node placement, reduced parasitics)

### 6.1 Toroid role (where it helps)
A toroidal metal top-load in Tesla coils increases capacitance and reduces field hotspots, which:
- reduces premature corona/leakage,
- forces discharge to engineered points.

In IX-Legacy terms, a toroid-like conductor can be used as:
- a controlled **E-field collector surface** (Module A coupling electrode) with smoother gradients,
- a **shield/guard** that stabilizes high-impedance nodes and reduces leakage,
- a repeatable geometry for measurement and enclosure consistency.

It does **not** create energy; it reduces loss and increases coupling reliability.

### 6.2 Triostrut role (where it helps)
A Triostrut node is treated as a deliberate “collection/transition node”:
- where wiring joins are mechanically stable,
- where you intentionally place measurement shunts / sense taps,
- where you intentionally localize a high-field point (if doing E-field coupling) with safe limits.

Again: not a generator—an engineered anchor point.

## 7) Control policy (high level)
Tri-Core Router control is a strict gatekeeper:

- SAFE_START:
  - RAILS_EN = OFF
  - PRECHARGE_EN = OFF
  - BYPASS_EN = OFF
  - DUMP_EN = OFF (unless service)
- HARVEST_ONLY:
  - accept module energy into cap via precharge policy (if required)
  - RAILS_EN remains OFF
- CHARGE / READY:
  - precharge storage connection; close bypass only when safe
- REGULATE:
  - enable rails if V_cap sufficient and thermal allows
  - enforce derating and load-shed
- FAULT:
  - rails OFF
  - isolate where possible
  - dump enabled only when required (e.g., overvoltage or service)

Implementation details are in firmware; this doc defines the contract.

## 8) Validation gates (router-specific)
To claim Tri-Core Router is “working,” we must demonstrate:
- Backfeed test: i_mod_i never goes negative beyond noise when bus is high.
- Precharge test: connecting storage does not cause damaging inrush; ΔV convergence logged.
- Dump test: storage can be discharged from max allowed V_cap to safe V in a measured time.
- Reconciliation test: E_in ≈ ΔE_cap + E_out + losses for a run window.

## 9) Scope note
IX-Legacy is a **non-weapon** energy harvesting + buffering platform. The Router design is focused
on safety, measurement integrity, and real external gradient capture.
