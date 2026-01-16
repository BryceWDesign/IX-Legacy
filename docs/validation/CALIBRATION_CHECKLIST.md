# File: docs/validation/CALIBRATION_CHECKLIST.md
# IX-Legacy — Calibration Checklist (v0)

## A) Shunt calibration (required)
For each shunt (modules and storage):
- Record part number and rated tolerance
- Measure resistance with a suitable meter (prefer 4-wire if available)
- Record measured value (ohms) and measurement method
- Record temperature during measurement (optional)

## B) Voltage divider calibration (required)
For each divider:
- Record resistor values and rated tolerances
- Measure divider ratio by applying a known voltage and measuring ADC input voltage
- Record ratio and reference voltage used

## C) ADC sanity check (required)
- Record ADC resolution (bits) and reference voltage
- Measure a known stable reference point and confirm conversion accuracy

## D) Timebase sanity check (required)
- Confirm sample interval dt is correct (compare firmware timestamps to wall-clock over 60–300s)

## E) Thermal sensor sanity check (required)
- Verify each temperature sensor reads ambient within expected tolerance
- If possible, apply a mild heat source and confirm response direction and plausibility

## F) Pre-run documentation (required)
Before claiming any measurement:
- Create a run folder name like: `runs/YYYY-MM-DD_env_summary/`
- Save: `calibration.json` (or `.md`), the raw CSV log, and a short run description
