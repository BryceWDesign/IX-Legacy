# File: hardware/TRIOSTRUT_NODE_NOTES.md
# IX-Legacy — Triostrut Node Hardware Notes (v0)

## 1) Electrical implementation posture
- Treat tri-nodes as *junction boards* or *junction blocks* with:
  - dedicated OR’ing devices where required
  - dedicated fuses per branch
  - shunt placements with Kelvin sense pads
  - labeled test points (TPs) for safe probing

## 2) Measurement posture
If a tri-node hosts a shunt:
- route current on thick copper / heavy conductors
- route sense on separate Kelvin traces/wires
- mechanically protect the sense leads from vibration

## 3) Mechanical posture
- Use a rigid mount (plate or standoff system) so the tri-node doesn’t flex
- Provide tie-down points for harness strain relief
- Keep heat-generating parts (OR FETs, rectifiers) thermally managed and sensor-tagged if needed

## 4) Cleanliness posture (especially for high impedance)
If tri-node touches high-impedance Module A circuitry:
- keep it clean and dry (leakage dominates at high impedance)
- avoid flux residue
- consider conformal coating only if it does not create additional leakage paths

## 5) Safety posture
Tri-nodes are where humans will probe. So:
- label test points clearly
- provide discharge verification points for Vcap
- avoid exposing high-potential nodes without insulation/guards
