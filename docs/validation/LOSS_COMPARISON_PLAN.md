# File: docs/validation/LOSS_COMPARISON_PLAN.md
# IX-Legacy — Loss Comparison Plan (v0)

## Goal
Quantify performance improvements from:
- ring-string topology,
- low-loss rectification,
- OR’ing discipline,
- Tri-Core Router gating.

## Comparisons
C1) Silicon bridge vs Schottky vs synchronous (same ring, same environment)
C2) Direct-parallel tubes vs ring-string buffered combining (same tube count, same environment)
C3) Rails always-on vs router-gated burst policy (same load profile)

## Metrics
- Joules harvested per minute (E_in / time)
- Joules stored per minute (ΔE_cap / time)
- Joules delivered per minute (E_out / time)
- E_loss breakdown
- thermal rise per delivered joule (ΔT / energy)

## Pass condition for “improvement”
An improvement claim is allowed only if:
- Energy Truth reconciliation closes for both cases, and
- net delivered/stored energy improves under identical environment constraints, and
- thermal behavior is not degraded beyond safe limits.
