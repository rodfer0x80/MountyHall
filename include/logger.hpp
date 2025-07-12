#pragma once

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>

enum LogLevel { DEBUG, INFO, WARN, ERROR };

static std::mutex log_mutex;

inline std::string current_timestamp() {
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);
  std::tm buf;

#if defined(_MSC_VER)
  localtime_s(&buf, &in_time_t);
#else
  localtime_r(&in_time_t, &buf);
#endif

  std::ostringstream ss;
  ss << std::put_time(&buf, "%d-%m-%Y %H:%M:%S");
  return ss.str();
}

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

  std::cout << "[" << current_timestamp() << "]"
            << " [" << level_str << "] " << msg << "\n";
}
