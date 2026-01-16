# File: docs/validation/REPRODUCIBILITY_CHECKLIST.md
# IX-Legacy — Reproducibility Checklist (v0)

A run is not “proof” unless this checklist is complete.

## A) Files present
- [ ] Raw CSV log present and readable
- [ ] Calibration sidecar present (`calibration.json` or equivalent)
- [ ] Run description present (environment + configuration)
- [ ] Validation report present (filled template)
- [ ] Firmware version recorded
- [ ] Photos or diagram of setup (recommended)

## B) Measurement integrity
- [ ] Module boundary measurements exist for every active module (V_mod_i, I_mod_i)
- [ ] Storage boundary measurements exist (V_cap, I_cap, T_cap)
- [ ] Output rail boundary exists if rails enabled (V_rail, I_rail, T_conv)
- [ ] dt is logged and plausible
- [ ] Sign conventions follow the protocol

## C) Calibration integrity
- [ ] Shunt values are measured (not nominal)
- [ ] Divider ratios are measured (not nominal)
- [ ] ADC ref + resolution recorded
- [ ] Temperature sensors sanity checked

## D) Reconciliation
- [ ] E_in computed
- [ ] ΔE_cap computed (both methods if possible)
- [ ] E_out computed if applicable
- [ ] E_loss is non-negative and explained
- [ ] Any discrepancy is discussed (noise floor, sampling error, etc.)

## E) Scope honesty
- [ ] Environment conditions are stated
- [ ] No universal claims are made without environment bounds
- [ ] Any “estimate” is labeled and assumptions are listed
