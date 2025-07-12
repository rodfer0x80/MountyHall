#pragma once
#include <iostream>
#include <mutex>
#include <string>

enum LogLevel { DEBUG, INFO, WARN, ERROR };

static std::mutex log_mutex;

inline void log(LogLevel level, const std::string &msg) {
  std::lock_guard<std::mutex> lock(log_mutex);
  const char *level_str = nullptr;
  switch (level) {
  case DEBUG:
    level_str = "DEBUG";
    break;
  case INFO:
    level_str = "INFO";
    break;
  case WARN:
    level_str = "WARN";
    break;
  case ERROR:
    level_str = "ERROR";
    break;
  }
  std::cout << "[" << level_str << "] " << msg << std::endl;
}
