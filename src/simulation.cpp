#include "simulation.hpp"

std::mutex file_mutex;

// Generate a random integer in [left, right] inclusive
int thread_randint(int left, int right) {
  static thread_local std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dist(left, right);
  return dist(rng);
}

void simulation_thread(int thread_id, int num_runs, std::string &thread_output,
                       const std::string &strategy) {
  std::ostringstream buffer;

  int losses = 0;
  int wins = 0;

  int door_pick = 0;
  int door_win = 0;
  int door_loss = 0;

  for (int i = 0; i < num_runs; ++i) {
    door_win = thread_randint(1, 3);
    door_pick = thread_randint(1, 3);

    if (door_pick == door_win) {
      if (door_pick == 1) {
        door_loss = thread_randint(2, 3);
      } else if (door_pick == 2) {
        door_loss = thread_randint(1, 3);
        while (door_pick == door_loss) {
          door_loss = thread_randint(1, 3);
        }
      } else { // door_pick == 3
        door_loss = thread_randint(1, 2);
      }
    } else {
      if (door_pick == 1 && door_win == 2) {
        door_loss = 3;
      } else if (door_pick == 1 && door_win == 3) {
        door_loss = 2;
      } else if (door_pick == 2 && door_win == 1) {
        door_loss = 3;
      } else if (door_pick == 2 && door_win == 3) {
        door_loss = 1;
      } else if (door_pick == 3 && door_win == 1) {
        door_loss = 2;
      } else if (door_pick == 3 && door_win == 2) {
        door_loss = 1;
      }
    }

    if (strategy == "switch") {
      if (door_pick == 1 && door_loss == 2) {
        door_pick = 3;
      } else if (door_pick == 1 && door_loss == 3) {
        door_pick = 2;
      } else if (door_pick == 2 && door_loss == 1) {
        door_pick = 3;
      } else if (door_pick == 2 && door_loss == 3) {
        door_pick = 1;
      } else if (door_pick == 3 && door_loss == 1) {
        door_pick = 2;
      } else if (door_pick == 3 && door_loss == 2) {
        door_pick = 1;
      }
    }

    if (door_pick == door_win) {
      wins += 1;
    } else {
      losses += 1;
    }
  }

  buffer << "runs:" << num_runs << "," << "strategy:" << strategy << ","
         << "wins:" << wins << ","
         << "losses:" << losses << "\n";
  thread_output = buffer.str();
}

void run_simulation(int num_run, const std::string &output_file) {
  const int num_threads = 4;
  const int num_strategies = 2;
  int threads_per_strategy = num_threads / num_strategies;
  int runs_per_thread = num_run / threads_per_strategy;
  int remainder = num_run % threads_per_strategy;
  
  std::vector<std::string> outputs(num_threads);
  std::array<std::thread, num_threads> threads;
  
  for (int strategy_id = 0; strategy_id < num_strategies; ++strategy_id) {
    std::string strategy_name = (strategy_id == 0) ? "hold" : "switch";

    for (int thread_idx = 0; thread_idx < threads_per_strategy; ++thread_idx) {
      int thread_id = strategy_id * threads_per_strategy + thread_idx;

      int runs_for_this_thread =
          runs_per_thread + (thread_idx < remainder ? 1 : 0);

      threads[thread_id] =
          std::thread(simulation_thread, thread_id + 1, runs_for_this_thread,
                      std::ref(outputs[thread_id]), strategy_name);
    }
  }

  for (auto &t : threads)
    t.join();

  std::lock_guard<std::mutex> lock(file_mutex);
  std::ofstream file(output_file, std::ios::app);
  if (!file) {
    std::cerr << "Failed to open output file: " << output_file << "\n";
    return;
  }
  for (const auto &line : outputs) {
    file << line;
  }
}
