#pragma once

#include <string>
#include <sys/stat.h>
#include <sys/types.h>

#include <logger.hpp>

inline void ensure_directory_exists(const std::string &path) {
  struct stat info;
  log(DEBUG, "Ensuring directory " + path + " exists ...");
  if (stat(path.c_str(), &info) != 0) {
    mkdir(path.c_str(), 0777);
    log(DEBUG, "Created new directory " + path);
  } else if (!(info.st_mode & S_IFDIR)) {
    log(ERROR, "Already exists directory " + path);
  }
}
