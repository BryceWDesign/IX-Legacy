# File: hardware/THERMAL_HARDWARE_NOTES.md
# IX-Legacy — Thermal Hardware Notes (v0)

## 0) Goal
Provide physical thermal design guidance that is conservative and test-driven.
No “magic cooling” claims.

## 1) Heat sources (typical)
- Switching MOSFETs
- Inductors (core + copper loss)
- Rectifiers / OR’ing elements
- Supercap ESR (I^2 * ESR during charge/discharge)

## 2) Passive thermal options (in order of simplicity)
- Heatsinks sized for measured dissipation
- Thermal pads / interface materials with known thickness and conductivity
- Heat spreaders (aluminum/copper plate)
- Heat pipes / vapor chambers (when spreading is needed)
- Phase-change material (PCM) for short bursts (thermal buffering, not continuous cooling)

## 3) Airflow / convection
- Forced airflow (fan) is the simplest controllable lever
- Ducting / baffles can increase effective airflow through hotspots
- Avoid recirculation zones by using flow guides in enclosure

## 4) Sensor placement rules
- Put the converter sensor where it is hottest, not where it is convenient
- Put the supercap sensor near the hottest cap in the bank (not at the edge)
- Secure sensors mechanically so readings track the real thermal mass

## 5) “TEG on heatsink” rule (optional reclaim)
- A TEG can reclaim some waste heat ONLY when there is a real ΔT across it.
- A TEG also adds thermal resistance; do not use it if it increases hotspot temperatures
  beyond safe limits.
- Any reclaimed power must be measured independently (no assumptions).

## 6) Build-to-test discipline
Thermal design must be validated by:
- measuring hotspot temps vs delivered watts,
- updating derating thresholds from real component limits,
- iterating heatsink/airflow until stability is demonstrated.

No README performance claims without this evidence.
