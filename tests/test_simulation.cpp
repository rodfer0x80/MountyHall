#include <fstream>
#include <regex>
#include <sstream>
#include <string>

#include <gtest/gtest.h>

#include "../include/simulation.hpp"
#include "../include/utils.hpp"

TEST(SimulationTest, OutputFileCreated) {
  std::string test_file = "./data/tests/output_file_created.csv";
  ensure_directory_exists("./data/tests");

  int num_runs = 1000;
  run_simulation(num_runs, test_file);

  std::ifstream infile(test_file);
  ASSERT_TRUE(infile.good());
}

TEST(SimulationTest, OutputFileNotEmpty) {
  std::string test_file = "./data/tests/output_file_not_empty.csv";
  ensure_directory_exists("./data/tests");

  int num_runs = 10000;
  run_simulation(num_runs, test_file);

  std::ifstream infile(test_file);
  std::stringstream buffer;
  buffer << infile.rdbuf();
  std::string content = buffer.str();
  ASSERT_FALSE(content.empty());
}

TEST(SimulationTest, OutputFormatIsCorrect) {
  std::string test_file = "./data/tests/output_format_is_correct.csv";
  ensure_directory_exists("./data/tests");

  int num_runs = 1000;
  run_simulation(num_runs, test_file);

  std::ifstream infile(test_file);
  std::string line;
  std::regex line_format(
      R"(runs:\d+,strategy:(switch|hold),wins:\d+,losses:\d+)");

  while (std::getline(infile, line)) {
    ASSERT_TRUE(std::regex_match(line, line_format))
        << "Invalid line format: " << line;
  }
}

TEST(SimulationTest, WinLossSumMatchesRuns) {
  std::string test_file = "./data/tests/win_loss_sum_matches_runs.csv";
  ensure_directory_exists("./data/tests");

  int num_runs = 1000;
  run_simulation(num_runs, test_file);

  std::ifstream infile(test_file);
  std::string line;
  int total_runs_reported = 0;
  int total_wins = 0;
  int total_losses = 0;

  while (std::getline(infile, line)) {
    size_t r_pos = line.find("runs:");
    size_t s_pos = line.find(",strategy:");
    int runs = std::stoi(line.substr(r_pos + 5, s_pos - r_pos - 5));

    size_t w_pos = line.find(",wins:");
    int wins =
        std::stoi(line.substr(w_pos + 6, line.find(",losses:") - w_pos - 6));

    int losses = std::stoi(line.substr(line.find(",losses:") + 8));

    total_runs_reported += runs;
    total_wins += wins;
    total_losses += losses;
  }

  int total_runs =
      num_runs *
      2; // num_runs = 1000 per strategy; 2 strategies -> 1000*2 == total_runs
  ASSERT_EQ(total_runs_reported, total_runs);
  ASSERT_EQ(total_wins + total_losses, total_runs);
}

TEST(SimulationTest, RemainderThreadSplitMatchesRuns) {
  std::string test_file = "./data/tests/remainder_thread_split_matches_run.csv";
  ensure_directory_exists("./data/tests");

  int num_runs = 3333;
  run_simulation(num_runs, test_file);

  std::ifstream infile(test_file);
  std::string line;
  int total_runs_reported = 0;
  int total_wins = 0;
  int total_losses = 0;

  while (std::getline(infile, line)) {
    size_t r_pos = line.find("runs:");
    size_t s_pos = line.find(",strategy:");
    int runs = std::stoi(line.substr(r_pos + 5, s_pos - r_pos - 5));

    size_t w_pos = line.find(",wins:");
    int wins =
        std::stoi(line.substr(w_pos + 6, line.find(",losses:") - w_pos - 6));

    int losses = std::stoi(line.substr(line.find(",losses:") + 8));

    total_runs_reported += runs;
    total_wins += wins;
    total_losses += losses;
  }

  int total_runs =
      num_runs *
      2; // num_runs = 1000 per strategy; 2 strategies -> 1000*2 == total_runs
  ASSERT_EQ(total_runs_reported, total_runs);
  ASSERT_EQ(total_wins + total_losses, total_runs);
}

TEST(SimulationTest, ProbabilitiesAsExpected) {
  std::string test_file = "./data/tests/probabilities_as_expected.csv";
  ensure_directory_exists("./data/tests");

  int num_runs = 1000000;
  run_simulation(num_runs, test_file);

  std::ifstream infile(test_file);
  std::string line;

  int runs_switch = 0, wins_switch = 0;
  int runs_hold = 0, wins_hold = 0;

  while (std::getline(infile, line)) {
    size_t r_pos = line.find("runs:");
    size_t s_pos = line.find(",strategy:");
    size_t w_pos = line.find(",wins:");
    size_t l_pos = line.find(",losses:");

    int runs = std::stoi(line.substr(r_pos + 5, s_pos - r_pos - 5));
    std::string strategy = line.substr(s_pos + 10, w_pos - s_pos - 10);
    int wins = std::stoi(line.substr(w_pos + 6, l_pos - w_pos - 6));

    if (strategy == "switch") {
      runs_switch += runs;
      wins_switch += wins;
    } else if (strategy == "hold") {
      runs_hold += runs;
      wins_hold += wins;
    }
  }

  double win_rate_switch = 100.0 * wins_switch / runs_switch;
  double win_rate_hold = 100.0 * wins_hold / runs_hold;

  EXPECT_NEAR(win_rate_switch, 66.0, 1.0);
  EXPECT_NEAR(win_rate_hold, 33.0, 1.0);
}
