# File: hardware/modules/MODULE_A_EFIELD_HARDWARE_NOTES.md
# IX-Legacy — Module A Hardware Notes (v0)

## 1) Layout priorities
- Keep the HV/high-Z front-end physically separated from low-voltage logic
- Use generous creepage/clearance on any node that can float high
- Minimize contamination/leakage (flux residue, dust, moisture) on high-impedance nodes

## 2) Enclosure considerations
- Electrode placement should be repeatable and documented
- Avoid exposed conductive surfaces that invite user contact
- Consider internal “guard” structures to stabilize coupling and reduce human-induced variance

## 3) Isolation and serviceability
- Provide a safe means to discharge any accumulated charge (bleed path + service note)
- Make the module removable without disturbing the backbone bus (precharge + OR’ing rules)
