#include <CLI11.hpp>
#include "worker.hpp"

int main(int argc, char *argv[]) {
  CLI::App app{"Multi-threaded job runner"};

  int num_loops = 100;
  std::string output_file = "output.txt";

  app.add_option("-n,--num", num_loops, "Number of loops per thread");
  app.add_option("-o,--output", output_file, "Output file name");

  CLI11_PARSE(app, argc, argv);

  run_threads(num_loops, output_file);
  return 0;
}
