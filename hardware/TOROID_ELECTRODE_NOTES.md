# File: hardware/TOROID_ELECTRODE_NOTES.md
# IX-Legacy — Toroid / Electrode Hardware Notes (v0)

## 1) Material posture
- Use conductive metals with stable surfaces (aluminum/copper/stainless) for repeatability.
- Insulation and spacing must be chosen for the maximum credible voltage the node can reach
  during operation (design conservatively).

## 2) Mounting posture
- Mount the electrode so its geometry is repeatable (fixed standoffs, no “floating around”).
- Avoid routing high-impedance sense traces across dirty/contaminated surfaces.

## 3) Service / cleanliness
High impedance = leakage-sensitive.
- Keep flux residue off high-Z areas.
- Avoid finger oils on collector surfaces during testing.
- Document cleaning procedure if needed.

## 4) Safety posture
This repo does not provide instructions for hazardous HV experiments.
Any high-potential electrode work must remain within safe, controlled, legal conditions.
