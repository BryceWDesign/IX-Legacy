# File: firmware/README.md
# IX-Legacy Firmware (v0)

## Purpose
Firmware provides a **safe, measurable control layer** for IX-Legacy:
- Enforces the state machine (safe start → harvest → charge → regulate → load-shed → fault)
- Implements ThermalGuardian derating + critical shutdown
- Logs “Energy Truth” telemetry (V/I/T + state) in a reproducible CSV format

This firmware is intentionally hardware-agnostic in v0. It is a scaffold to be bound to
real sensors, shunts, and converters in later hardware commits.

## State machine (canonical)
- SAFE_START: initialize, confirm sensors sane, conversion OFF
- HARVEST_ONLY: accept harvester input to storage, conversion OFF
- CHARGE: precharge logic + storage charging; conversion OFF unless configured otherwise
- REGULATE: enable rails when buffer permits and thermal allows
- LOAD_SHED: reduced rails / limited output when buffer low or thermal amber
- FAULT_LATCHED: conversion OFF; latch faults; optional dump path control

## “Energy Truth” logging
Logs must align with:
- docs/validation/LOG_FIELDS.md
- docs/04_ENERGY_TRUTH_PROTOCOL.md

Baseline output is CSV over serial. SD logging is stubbed for later.

## Non-negotiables
- No backfeed assumptions. Hardware must enforce OR’ing; firmware detects anomalies.
- Precharge must be satisfied before closing bypass (where implemented).
- Thermal critical overrides all other goals.

## Build system
This is written in a PlatformIO-style layout (src/include). You may adapt it to Arduino,
STM32, ESP32, etc. Binding to real ADC channels and current monitors is future work.
