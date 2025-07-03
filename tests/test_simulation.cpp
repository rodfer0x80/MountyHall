#include <fstream>

#include <gtest/gtest.h>

#include "../include/simulation.hpp"

TEST(WorkerTest, OutputFileCreated) {
  std::string test_file = "./data/test_output.txt";
  int num_runs = 100;
  run_simulation(num_runs, test_file);

  std::ifstream infile(test_file);
  ASSERT_TRUE(infile.good());
}
