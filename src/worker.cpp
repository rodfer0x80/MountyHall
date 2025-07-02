#include <fstream>
#include <mutex>
#include <thread>

#include "worker.hpp"

std::mutex file_mutex;

void thread_task(int thread_id, int loops, const std::string &output_file) {
  std::ofstream file;
  for (int i = 0; i < loops; ++i) {
    std::lock_guard<std::mutex> lock(file_mutex);
    file.open(output_file, std::ios::app);
    file << "Thread " << thread_id << " iteration " << i << "\n";
    file.close();
  }
}

void run_threads(int num_loops, const std::string &output_file) {
  int loops_per_thread = num_loops / 4;
  std::thread t1(thread_task, 1, loops_per_thread, output_file);
  std::thread t2(thread_task, 2, loops_per_thread, output_file);
  std::thread t3(thread_task, 3, loops_per_thread, output_file);
  std::thread t4(thread_task, 4, loops_per_thread, output_file);

  t1.join();
  t2.join();
  t3.join();
  t4.join();
}
