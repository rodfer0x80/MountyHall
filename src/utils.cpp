#include "utils.hpp"

void ensure_directory_exists(const std::string &path) {
  struct stat info;
  if (stat(path.c_str(), &info) != 0) {
    mkdir(path.c_str(), 0777);
  } else if (!(info.st_mode & S_IFDIR)) {
    // Exists but not a directory
  }
}
