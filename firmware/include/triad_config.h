# File: firmware/include/triad_config.h
#pragma once

// Triad role configuration (v0: fixed roles by build-time define).
// Exactly one unit should be built/flashed with each role.
// If not using triad mode, set ROLE_SINGLE.

enum class TriadRole : uint8_t {
  ROLE_SINGLE = 0,
  ROLE_BUFFER_MASTER,
  ROLE_CONVERSION_MASTER,
  ROLE_SENSE_MASTER
};

// ---- Set this per build ----
#ifndef IX_LEGACY_TRIAD_ROLE
#define IX_LEGACY_TRIAD_ROLE 0
#endif

static constexpr TriadRole TRIAD_ROLE = static_cast<TriadRole>(IX_LEGACY_TRIAD_ROLE);

// Control link is a stub in v0; this defines message intent, not a full stack.
static constexpr uint32_t TRIAD_HEARTBEAT_MS = 500;
