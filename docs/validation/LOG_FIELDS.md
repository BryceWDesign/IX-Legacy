# File: docs/validation/LOG_FIELDS.md
# IX-Legacy — Canonical Log Fields (v0)

## 1) Format
CSV is the baseline for portability. Each row is a sample at time t.

## 2) Required base columns
- ts_ms: integer timestamp in milliseconds since run start
- dt_ms: integer delta-time since prior sample (ms). Must be present for integration.
- run_id: short id or filename stem (optional but recommended)

## 3) Required electrical columns (minimum viable)
### Storage
- v_cap_v: supercap voltage (V)
- i_cap_a: supercap current (A) (+charge, -discharge)
- t_cap_c: supercap temperature (°C)

### Output rails (at least one if conversion is enabled)
- v_rail_5v_v: 5V rail voltage (V) (omit if not present)
- i_rail_5v_a: 5V rail current (A)
- v_rail_12v_v: 12V rail voltage (V) (omit if not present)
- i_rail_12v_a: 12V rail current (A)

### Converter thermal (if any rail enabled)
- t_conv_c: converter hotspot temperature (°C)

## 4) Per-module columns (repeat per module index)
For each module i, include:
- v_mod{i}_v: module output voltage into bus (V)
- i_mod{i}_a: module current into bus (A)
- t_mod{i}_c: module hotspot temperature (°C) (optional)

Example:
- v_mod1_v, i_mod1_a, t_mod1_c
- v_mod2_v, i_mod2_a, t_mod2_c
...

## 5) Calibration metadata (required but may be stored as a header block or sidecar file)
At minimum record:
- shunt_ohms_mod{i}: measured shunt resistance for module i
- shunt_ohms_cap: measured shunt resistance for storage current
- div_ratio_cap: measured divider ratio for v_cap
- div_ratio_rail_5v / 12v: measured divider ratios
- adc_ref_v: ADC reference voltage used
- adc_bits: ADC resolution

Sidecar file recommendation:
- `calibration.json` stored alongside the run log.

## 6) Units
All numeric columns must be in SI units as shown (V, A, °C, ms).

## 7) Missing data rule
If a channel is not instrumented, it must not appear.
Do not fill with zeros unless it is truly measured as zero.
