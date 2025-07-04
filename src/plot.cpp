#include "plot.hpp"
namespace plt = matplotlibcpp;

void render_plot(std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << filename << "\n";
    return;
  }

  std::map<std::string, int> total_wins, total_games;
  std::string line;

  // Read and parse data
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string strategy;
    int wins = 0, losses = 0;

    // Simple parsing: strategy:X,wins:Y,losses:Z
    if (line.find("hold") != std::string::npos)
      strategy = "Hold";
    else if (line.find("switch") != std::string::npos)
      strategy = "Switch";

    size_t pos = line.find("wins:");
    if (pos != std::string::npos) {
      wins = std::stoi(line.substr(pos + 5));
    }
    pos = line.find("losses:");
    if (pos != std::string::npos) {
      losses = std::stoi(line.substr(pos + 7));
    }

    total_wins[strategy] += wins;
    total_games[strategy] += wins + losses;
  }
  file.close();

  std::vector<std::string> strategies;
  std::vector<double> win_rates;

  for (auto &pair : total_wins) {
    strategies.push_back(pair.first);
    double rate = (double)pair.second / total_games[pair.first] * 100.0;
    win_rates.push_back(rate);
  }

  plt::figure_size(800, 1200);
  std::vector<double> x_pos = {0, 1};
  plt::bar(std::vector<double>{x_pos[0]}, std::vector<double>{win_rates[0]},
           "blue");
  plt::bar(std::vector<double>{x_pos[1]}, std::vector<double>{win_rates[1]},
           "orange");
  for (size_t i = 0; i < x_pos.size(); ++i) {
    char label[10];
    snprintf(label, sizeof(label), "%.1f%%", win_rates[i]);
    plt::text(x_pos[i], win_rates[i] + 2, label);
  }
  plt::xticks(x_pos, strategies);
  plt::xlabel("Strategy");
  plt::ylabel("Win Rate (%)");
  plt::title("Monty Hall Simulation");
  plt::ylim(0, 110); 
  plt::show();
}
