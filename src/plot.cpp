#include "plot.hpp"
#include "logger.hpp"

namespace plt = matplotlibcpp;

void render_plot(std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    log(ERROR, "Failed to open file: " + filename);
    return;
  }

  std::map<std::string, int> total_wins, total_games;
  std::string line;
  
  log(DEBUG, "Parsing data from " + filename + " ...");
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string strategy;
    int wins = 0, losses = 0;

    // format => strategy:X,wins:Y,losses:Z
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

  int plot_width = 600;
  int plot_height= 600;
  log(DEBUG, "Generating plot ...");
  plt::figure_size(plot_width, plot_height);
  log(DEBUG, "Plot dimensions " + std::to_string(plot_width) + "x" + std::to_string(plot_height));
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
  std::string img_filename = filename;
  size_t ext_pos = img_filename.rfind(".csv");
  if (ext_pos != std::string::npos) {
    img_filename.replace(ext_pos, 4, ".png");
  } else {
    img_filename += ".png";
  }
  plt::save(img_filename);
  log(INFO, "Saved plot data to " + img_filename);
  // plt::show();
}
