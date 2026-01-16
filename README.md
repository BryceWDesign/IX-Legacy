# README.md
# IX-Legacy

**Status:** Evaluation / Prototype Architecture (Source-Available, Internal Evaluation + Validation Only)  
**License:** See `LICENSE` (Commercial/production use requires a separate written agreement with **Bryce Lovell**.)

## What this is
IX-Legacy is a **multi-input energy scavenging + supercapacitor buffering platform** built to be:
- **Physics-clean:** no “overunity,” no hidden inputs, no vague “ambient” claims without measured bounds.
- **Measurable:** strict input/output energy accounting with reproducible logs.
- **Safe:** precharge, no-backfeed combining, dump/discharge path, fault interlocks, and thermal derating.
- **Modular:** independent harvester front-ends feeding a shared storage + conversion spine.

### Real input channels (environment-dependent)
- **Module A:** E-field capacitive coupling (trickle contributor, environment dominated)
- **Module B:** Vibration/kinetic (electromagnetic tubes + tuned ring strings; primary where vibration exists)
- **Module C:** Thermal ΔT (TEG; strong when a real heat flow exists)
- **Module R (optional):** RF rectenna tile skin (typically µW–mW unless near strong transmitters)

## What this is NOT
- Not a weapon, not weapon-adjacent, and not designed for harm.
- Not a “free energy” device. It only harvests energy from **real external gradients** that exist in the environment.
- Not production-ready in this repository form.

## The core idea
Many weak inputs charge one shared buffer, and one controlled hub releases power to loads:

**Harvesters → (safe combine) → Supercap Buffer → (gated conversion) → Regulated Rails**

The “center action” is handled by the **Tri-Core Router**.

## Tri-Core Router (center hub)
Tri-Core Router is the single throat that makes IX-Legacy credible:
- Combines multiple sources safely (**no backfeed**, no source-fighting)
- Manages storage connection (**precharge + bypass**)
- Provides safe discharge (**dump path**)
- Gates rails based on **buffer + thermal + fault state**
- Enforces the measurement boundaries required for proof (“Energy Truth”)

Read: `docs/08_TRI_CORE_ROUTER.md`

## Borromean / Gankyil mapping (engineering, not mysticism)
Three interdependent subsystems must all be present:
1) **Energy Buffer/Storage Core** — supercaps + balancing + dump/discharge + health signals  
2) **Conversion Core** — efficient conversion + rail gating + load shedding  
3) **Sense/Control Core** — energy accounting + ThermalGuardian + faults/interlocks  

Triad mode (optional): three identical devices can link into a **Gankyil Triad** with fixed roles:
- Buffer Master / Conversion Master / Sense Master  
Read: `docs/12_GANKYIL_TRIAD_INTERCONNECT.md`

## Validation: no claims without proof
No performance claim is allowed without:
- following `docs/04_ENERGY_TRUTH_PROTOCOL.md`
- producing a run folder like `runs/YYYY-MM-DD_env_summary/`
- completing `docs/validation/REPORT_TEMPLATE.md`
- passing `docs/validation/REPRODUCIBILITY_CHECKLIST.md`

Tri-Core specific test plan:
- `docs/validation/TRI_CORE_TESTS.md`
- `docs/validation/LOSS_COMPARISON_PLAN.md`

Example structure:
- `runs/EXAMPLE_RUN/`

## Repository layout
- `docs/`  
  - Architecture: `docs/01_ARCHITECTURE_OVERVIEW.md`  
  - Tri-Core Router: `docs/08_TRI_CORE_ROUTER.md`  
  - Bus rules: `docs/05_COMMON_BUS_SPEC.md`  
  - ThermalGuardian: `docs/07_THERMAL_GUARDIAN.md`  
  - Triad interconnect: `docs/12_GANKYIL_TRIAD_INTERCONNECT.md`  
  - Modules:
    - `docs/modules/MODULE_A_EFIELD.md`
    - `docs/modules/MODULE_B_VIBRATION.md`
    - `docs/modules/MODULE_C_THERMAL_TEG.md`
    - `docs/modules/MODULE_R_RF_RECTENNA.md`
- `hardware/` — hardware guidance + module notes (mechanical, thermal, node discipline)
- `firmware/` — state machine + logging scaffold + EnergyRouter policy layer
- `runs/` — reproducible measurement runs (raw logs + calibration + reports)

## How to evaluate (high-level)
1) Pick the environment and the modules you can realistically exploit (vibration/ΔT/E-field/RF).
2) Instrument per the Energy Truth Protocol.
3) Run harvest-only first (prove net energy into storage).
4) Enable rails and test duty-cycled loads with ThermalGuardian limits.
5) Publish Evaluation Results (allowed) without disclosing Materials (see LICENSE).

## Commercial/production licensing & contact
The repository is **evaluation/validation only**.  
If your organization wants to manufacture, deploy, distribute, or commercialize IX-Legacy, you must obtain a separate written license from **Bryce Lovell**.

(If you’re evaluating internally and want to share measured results publicly, you may do so per the `LICENSE` while keeping the Materials private.)
