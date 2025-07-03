#pragma once

#include <string>
#include <sys/stat.h>
#include <sys/types.h>

void ensure_directory_exists(const std::string &path);
