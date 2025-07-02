#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>

#include "simulation.hpp"

std::mutex file_mutex;

void simulation_thread(int thread_id, int num_runs, std::string &thread_output,
                       const std::string &strategy) {
  std::ostringstream buffer;
  for (int i = 0; i < num_runs; ++i) {
    buffer << "thread: " << thread_id << " - simulation: " << i
           << " - strategy: " << strategy << "\n";
  }
  thread_output = buffer.str(); 
}

void run_simulation(int num_loops, const std::string &output_file) {
  int num_runs_per_thread = num_loops / 2;
  std::string output1, output2, output3, output4;

  std::thread t1(simulation_thread, 1, num_runs_per_thread, std::ref(output1), "hold");
  std::thread t2(simulation_thread, 2, num_runs_per_thread, std::ref(output2), "hold");
  std::thread t3(simulation_thread, 3, num_runs_per_thread, std::ref(output3), "switch");
  std::thread t4(simulation_thread, 4, num_runs_per_thread, std::ref(output4), "switch");

  t1.join();
  t2.join();
  t3.join();
  t4.join();

  std::ofstream file(output_file, std::ios::app);
  if (!file.is_open()) {
    std::cerr << "Failed to open output file: " << output_file << "\n";
    return;
  }
  file << output1 << output2 << output3 << output4;
}

