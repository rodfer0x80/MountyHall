#pragma once

#include <array>
#include <fstream>
#include <iostream>
#include <mutex>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <vector>


int thread_randint(int left, int right);

void simulation_thread(int thread_id, int num_runs, std::string &thread_output,
                       const std::string &strategy);

void run_simulation(int num_loops, const std::string &output_file);
