# File: docs/04_ENERGY_TRUTH_PROTOCOL.md
# IX-Legacy — Energy Truth Protocol (v0)

## 0) Purpose
This protocol exists to prevent false conclusions. IX-Legacy must be able to prove, with
repeatable logs, that:
- energy harvested (input) is real,
- energy stored (buffer) is real,
- energy delivered (output) is real,
- and losses are explainable (conversion inefficiency, wiring loss, leakage, heat).

No README claim is allowed without logs produced by this protocol.

## 1) Measurement philosophy (non-negotiable)
1) Measure **both** voltage and current wherever power is claimed.
2) Measure at the **correct boundary** (module-to-bus, bus-to-storage, storage-to-rails).
3) Log raw samples + calibration constants.
4) Reconcile energy using consistent sign conventions.

## 2) Minimum measurement points
### 2.1 Per-harvester module boundary (required)
For each module i:
- V_mod_i: voltage at the module output just before OR’ing into the common bus
- I_mod_i: current from module into the bus (positive when module sources power)
- T_mod_i (optional): temperature at module rectifier/MPPT hotspot

### 2.2 Storage boundary (required)
- V_cap: supercap bank voltage
- I_cap: current into the supercap bank (positive when charging, negative when discharging)
- T_cap: temperature at/near supercap bank

### 2.3 Output rails boundary (required)
For each rail r (e.g., 5V, 12V):
- V_rail_r: rail voltage at the load distribution point
- I_rail_r: rail current delivered to loads (positive when sourcing power)
- T_conv: converter hotspot temperature (inductor/MOSFET heatsink area)

### 2.4 Bus boundary (recommended)
- V_bus: common bus voltage (post-OR’ing, pre-storage)
- I_bus (optional): total bus current into storage/conversion

## 3) Sign convention (critical)
- Module current I_mod_i is **positive** when energy flows from module → bus
- Storage current I_cap is **positive** when energy flows bus → supercaps (charging)
- Storage discharge is I_cap **negative** (supercaps → conversion/loads)
- Rail current I_rail is **positive** when energy flows converter → loads

## 4) Energy reconciliation math (what we compute)
Use discrete-time integration at sample interval dt:

### 4.1 Per-module harvested energy
E_in = Σ_i Σ_k (V_mod_i[k] * I_mod_i[k] * dt)

### 4.2 Change in stored energy (supercap)
Approximate using capacitor energy:
E_cap(t) = 0.5 * C_total * V_cap(t)^2
ΔE_cap = E_cap(t_end) - E_cap(t_start)

(If C_total is uncertain, compute ΔE_cap by integrating V_cap * I_cap * dt and compare.)

### 4.3 Delivered energy to loads
E_out = Σ_r Σ_k (V_rail_r[k] * I_rail_r[k] * dt)

### 4.4 Losses / overhead
E_loss ≈ E_in - ΔE_cap - E_out

We expect E_loss >= 0 and explainable by:
- conversion inefficiency
- diode/OR’ing drop
- wiring/trace resistance
- supercap ESR heating + leakage
- controller overhead

If E_loss < 0, measurement is wrong or sign conventions are broken.

## 5) Instrumentation recommendations (test-grade)
### 5.1 Current sensing
Preferred:
- precision shunt resistors (4-terminal/Kelvin), sized for expected currents
- differential amplifier or dedicated current monitor IC
- avoid “estimated current” from converter telemetry when proving claims

Rule of thumb:
- choose shunt so max expected current produces 25–100 mV drop (keeps loss small but measurable)

### 5.2 Voltage sensing
- resistor divider into ADC with known tolerance
- measure divider ratio and store it as a calibration constant

### 5.3 Sampling rate
- For slow harvesters (TEG/PV/E-field): 1–10 Hz can be enough
- For vibration harvesters: log at 10–100 Hz at the bus boundary, or compute RMS at higher internal
  sampling and log aggregated values
- Always record dt precisely

## 6) Calibration (required before any “proof” run)
Calibration must be documented for:
- each shunt resistance value (actual measured)
- ADC scale/offset for each channel
- divider ratio actual measured
- timebase (dt) sanity check

See `docs/validation/CALIBRATION_CHECKLIST.md`.

## 7) Required test run structure (no exceptions)
Each claim requires a run that includes:
1) Environment description:
   - vibration source (if any): approximate frequency/acceleration or qualitative description
   - ΔT measurement for TEG (hot/cold side temperatures)
   - lighting conditions for PV
   - E-field proximity description for capacitive harvesting
   - RF environment description (location + bands if known)
2) System configuration:
   - module set present
   - storage C_total and voltage limits
   - conversion rails enabled/disabled
   - load profile (constant load or duty cycle)
3) Logs:
   - raw timeseries logs per schema
   - instrument list used and calibration constants
4) Reconciliation report:
   - E_in, ΔE_cap, E_out, E_loss
   - plots (optional) and explanation of discrepancies

## 8) Log format (canonical)
IX-Legacy logs MUST conform to:
- `docs/validation/LOG_FIELDS.md`
- `docs/validation/log_schema_example.csv`

## 9) Claim policy (locked)
- Any “measured” number must link to a run directory and reconciliation report.
- If a number is estimated, it must be labeled **ESTIMATE** and list assumptions.
- If a number is a goal, it must be labeled **TARGET** and must not be presented as achieved.
