// File: firmware/include/config.h
#pragma once

// ---------- Firmware identity ----------
#define IX_LEGACY_FW_VERSION "0.1.0"

// ---------- Timing ----------
static constexpr uint32_t LOG_INTERVAL_MS = 1000;   // 1 Hz baseline logging for v0
static constexpr uint32_t CONTROL_INTERVAL_MS = 100; // 10 Hz control loop

// ---------- ThermalGuardian parameters (placeholders; bind to real components later) ----------
static constexpr float T_CONV_AMBER_C = 70.0f;
static constexpr float T_CONV_RED_C   = 90.0f;
static constexpr float T_CONV_RESET_C = 60.0f;

static constexpr float T_CAP_AMBER_C  = 55.0f;
static constexpr float T_CAP_RED_C    = 70.0f;
static constexpr float T_CAP_RESET_C  = 45.0f;

// ---------- Voltage thresholds (placeholders; bind to bus/cap design later) ----------
static constexpr float V_CAP_MIN_ENABLE_RAILS_V = 6.0f;     // minimum cap voltage to enable rails
static constexpr float V_CAP_MIN_LOGIC_V        = 3.0f;     // minimum cap voltage to keep MCU alive (concept)
static constexpr float V_CAP_OVERVOLT_V         = 16.0f;    // overvoltage fault threshold (placeholder)

// ---------- Precharge policy (placeholder) ----------
static constexpr float PRECHARGE_DV_THRESHOLD_V = 0.3f;     // |V_bus - V_cap| must be below this to close bypass
static constexpr uint32_t PRECHARGE_TIMEOUT_MS  = 10'000;   // 10 seconds
static constexpr uint32_t PRECHARGE_DWELL_MS    = 500;      // must remain below threshold for this long
