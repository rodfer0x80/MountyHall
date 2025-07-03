#include "plot.hpp"

namespace plt = matplotlibcpp;

void render_plot(std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << filename << "\n";
    return;
  }

  std::map<std::string, std::vector<int>> wins, losses;

  std::string line;
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string token;
    std::string strategy;
    int win_count = 0, loss_count = 0;

    while (std::getline(ss, token, ',')) {
      auto pos = token.find(':');
      if (pos == std::string::npos)
        continue;
      std::string key = token.substr(0, pos);
      std::string value = token.substr(pos + 1);

      if (key == "strategy")
        strategy = value;
      else if (key == "wins")
        win_count = std::stoi(value);
      else if (key == "losses")
        loss_count = std::stoi(value);
    }

    if (!strategy.empty()) {
      wins[strategy].push_back(win_count);
      losses[strategy].push_back(loss_count);
    }
  }

  file.close();

  // Prepare averages for plotting
  std::vector<std::string> strategies;
  std::vector<double> avg_wins, avg_losses;
  for (const auto &[strategy, win_vals] : wins) {
    double win_sum = 0, loss_sum = 0;
    for (int w : win_vals)
      win_sum += w;
    for (int l : losses[strategy])
      loss_sum += l;

    strategies.push_back(strategy);
    avg_wins.push_back(win_sum / win_vals.size());
    avg_losses.push_back(loss_sum / losses[strategy].size());
  }

  // Plotting
  std::vector<double> x;
  for (size_t i = 0; i < strategies.size(); ++i)
    x.push_back(i);

  double bar_width = 0.4;

  plt::figure_size(800, 600);
  plt::bar(x, avg_wins, "green", "", bar_width, {{"label", "Wins"}});
  std::vector<double> x_shifted = x;
  for (double &xi : x_shifted)
    xi += bar_width;
  plt::bar(x_shifted, avg_losses, "red", "", bar_width, {{"label", "Losses"}});

  // Label x-axis
  std::vector<double> xticks;
  for (double xi : x)
    xticks.push_back(xi + bar_width / 2.0);
  plt::xticks(xticks, strategies);
  plt::ylabel("Average Count");
  plt::title("Strategy Performance: Wins vs Losses");
  plt::legend();
  plt::tight_layout();
  plt::save("strategy_plot.png");
  plt::show();
}
