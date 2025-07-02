#include "simulation.hpp"
#include <CLI11.hpp>

int main(int argc, char *argv[]) {
  CLI::App app{"Mounty Hall Simulation"};

  int num_runs = 100;
  std::string output_file = "output.txt";
  bool graph_ui = false;

  app.add_option("-n,--num", num_runs, "Number of simulation to run");
  app.add_option("-o,--output", output_file, "Output file name");
  app.add_option("-g,--graph", graph_ui, "Render stats in a graphic UI");

  CLI11_PARSE(app, argc, argv);

  run_simulation(num_runs, output_file);
  run_simulation(num_runs, output_file);
  if (graph_ui) {
    // render_graph();
  }
  return 0;
}
