// File: firmware/include/logger.h
#pragma once
#include "types.h"

class Logger {
public:
  void begin();
  void log_header();
  void log_row(const Telemetry& t);

private:
  bool header_written_ = false;
};
