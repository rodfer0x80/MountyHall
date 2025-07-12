#include <CLI11.hpp>

#include "plot.hpp"
#include "simulation.hpp"
#include "utils.hpp"

int main(int argc, char *argv[]) {
  CLI::App app{"Mounty Hall Simulation"};

  int num_runs = 100;
  bool plot = false;
  std::string output_file = "./data/output.csv";
  ensure_directory_exists("./data");
  ensure_directory_exists("./data/tests");

  app.add_option("-n,--num", num_runs, "Number of simulation to run");
  app.add_option("-o,--output", output_file, "Output file name (CSV)");
  app.add_flag("-p,--plot", plot, "Render stats in a plot UI");

  CLI11_PARSE(app, argc, argv);

  run_simulation(num_runs, output_file);
  if (plot)
    render_plot(output_file);
  
  return 0;
}
