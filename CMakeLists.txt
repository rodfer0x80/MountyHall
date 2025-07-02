cmake_minimum_required(VERSION 3.14)
project(MountyHall VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Include directories ----
include_directories(include)

# ---- Main app ----
add_executable(MountyHall
  src/main.cpp
  src/worker.cpp
)

# ---- GoogleTest setup ----
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_executable(test_worker
  tests/test_worker.cpp
  src/worker.cpp
)

target_include_directories(test_worker PRIVATE include)
target_link_libraries(test_worker
  GTest::gtest
  GTest::gtest_main
  pthread
)

gtest_discover_tests(test_worker
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  DISCOVERY_TIMEOUT 10
)

