# File: docs/01_ARCHITECTURE_OVERVIEW.md
# IX-Legacy — Architecture Overview (v0)

## 1) Top-level concept
IX-Legacy is a modular “OmniHarvester + Supercap UPS” platform:

Ambient Gradient(s)
  ├─ Harvester Module A (E-field / capacitive coupling)
  ├─ Harvester Module B (Vibration / linear EM / electret / piezo as applicable)
  ├─ Harvester Module C (Thermal / TEG)
  └─ (Optional) Harvester Module R (RF rectenna tiles)
        │
        ▼
  [Front-end Conditioning]
   - Low-loss rectification (or direct DC where applicable)
   - Impedance control / MPPT (as applicable)
   - Per-module input measurement (V/I)
        │
        ▼
  [Common DC Harvest Bus]
   - Ideal-diode OR’ing per module (no backfeed)
   - Fuse isolation per module
   - Controlled precharge path to avoid inrush
        │
        ▼
  [Energy Buffer / Storage]
   - Supercap bank (serviceable)
   - Balancing / overvoltage protection
   - Safe discharge (“dump path”) + service procedure
   - Storage health metrics (ESR proxy, temp, leakage proxy)
        │
        ▼
  [Power Conversion]
   - Efficient conversion from supercap bus to regulated rails (5V/12V/etc.)
   - Brownout rules + load shedding
        │
        ▼
  [Loads]
   - Sensors / MCU / telemetry
   - Intermittent high draw allowed only when buffer permits

## 2) Borromean mapping (non-negotiable)
A) Buffer/Storage — supercaps + balancing + dump/load safety
B) Conversion/Pulse shaping — conversion sized to *measured* available input
C) Sensing/Feedback — prevents self-deception; enforces thermal and electrical limits

If any one subsystem is missing, the platform becomes either unsafe, unmeasurable, or non-functional.

## 3) Gankyil triad mode (optional deployment topology)
Three identical IX-Legacy units can be linked into a single system via:
- A shared backbone DC bus (with per-unit ideal-diode OR’ing + fusing)
- A shared telemetry/control link (RS-485/CAN)
- Master election or fixed roles (Buffer Master / Conversion Master / Sense Master)

Key rule: Triad yields true multi-x gains only when each lobe has access to *independent* external gradients.

## 4) Interfaces (v0)
### 4.1 Harvester module electrical interface (to the common bus)
Each harvester module must provide:
- Output: conditioned DC into the bus via OR’ing + fuse
- Telemetry: module V_in, I_in (and temp if relevant)
- Control (optional): enable/disable, MPPT/impedance setpoint

### 4.2 Storage interface
- Supercap bus V_cap, I_cap (charge/discharge), T_cap
- Balancer status
- Dump/load state

### 4.3 Conversion interface
- Rail voltages and currents
- Converter temperatures
- Load shed state and fault flags

## 5) Safety invariants (must always hold)
- No module can backfeed any other module
- Precharge required before connecting large capacitances
- Dump path must be available whenever supercap bank is connected
- Thermal derating must override power delivery
