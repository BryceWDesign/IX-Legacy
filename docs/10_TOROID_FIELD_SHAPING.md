# File: docs/10_TOROID_FIELD_SHAPING.md
# IX-Legacy — Toroid Field-Shaping Notes (v0)

## 0) Why this exists
In Tesla coils, a toroidal top-load is used to:
- increase effective capacitance at the high-potential end,
- smooth electric-field gradients,
- reduce unwanted corona/leakage,
- force discharge to a controlled point (breakout tip).

IX-Legacy uses the same *engineering idea* (field shaping), but **not** to “create energy.”
This is about **reducing losses, stabilizing coupling, and making behavior repeatable.**

## 1) What a “toroid” means in IX-Legacy
In IX-Legacy, “toroid” means a smooth, rounded conductive geometry used as one of:
A) A controlled **E-field coupling electrode** (Module A)
B) A **guard/shield** for high-impedance nodes (reduces leakage and touch/handling variability)
C) A **field smoother** that reduces sharp-edge hotspots that waste charge as corona

Key benefit: the toroid helps ensure “the field goes where we want it to,” instead of bleeding
into random edges, seams, fasteners, or wiring.

## 2) How it helps Module A (E-field harvester)
Module A performance depends heavily on:
- electrode geometry,
- leakage paths,
- and repeatability.

A toroid-like electrode:
- provides a large, smooth collection surface,
- reduces edge corona/leakage compared to sharp features,
- stabilizes capacitive coupling so results don’t swing wildly with tiny geometry changes.

## 3) How it helps measurement integrity (“Energy Truth”)
High-impedance nodes are prone to:
- leakage through contamination (dust/moisture/flux residue),
- stray coupling into nearby switching nodes,
- human touch coupling that changes readings.

A toroid used as a guard/shield can:
- reduce measurement drift,
- reduce “mystery charge” accumulation,
- and improve repeatability of tests across runs.

## 4) What it cannot do (locked reality check)
- It cannot generate net power.
- It cannot multiply energy input.
- It cannot replace the need for a real external gradient (E-field present in the environment).

Any performance improvement is limited to:
- reduced losses,
- improved coupling efficiency,
- improved repeatability.

## 5) Practical design rules (geometry-first, not magic)
- Avoid sharp edges and points on any conductor intended to hold high potential or high impedance.
- Prefer smooth radii and continuous surfaces.
- Keep high-impedance “collector” surfaces physically separated from noisy switching converters.
- If you must route wiring near the toroid/electrode, route it symmetrically to reduce unintended coupling.

## 6) Validation gate (must be proven)
Toroid field-shaping is considered “helpful” only if logs show:
- improved net harvested energy under the same environment,
- reduced variability between runs,
- and no increase in unexplained losses (corona/leakage/overhead).

All proof must follow `docs/04_ENERGY_TRUTH_PROTOCOL.md`.
