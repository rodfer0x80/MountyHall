#include <fstream>

#include <gtest/gtest.h>

#include "../include/worker.hpp"

TEST(WorkerTest, OutputFileCreated) {
  std::string test_file = "test_output.txt";
  run_threads(20, test_file);

  std::ifstream infile(test_file);
  ASSERT_TRUE(infile.good());
}
