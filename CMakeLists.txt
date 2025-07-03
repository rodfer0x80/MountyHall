cmake_minimum_required(VERSION 3.14)
project(MountyHall VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Include directories ----
include_directories(include)

# ---- Main app ----
add_executable(MountyHall
  src/main.cpp
  src/utils.cpp
  src/plot.cpp
  src/simulation.cpp
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

add_executable(test_utils
  tests/test_utils.cpp
  src/utils.cpp
)

target_include_directories(test_utils PRIVATE include)
target_link_libraries(test_utils
  GTest::gtest
  GTest::gtest_main
)

gtest_discover_tests(test_utils
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  DISCOVERY_TIMEOUT 10
)

add_executable(test_simulation
  tests/test_simulation.cpp
  src/utils.cpp
  src/simulation.cpp
)

target_include_directories(test_simulation PRIVATE include)
target_link_libraries(test_simulation
  GTest::gtest
  GTest::gtest_main
  pthread
)

gtest_discover_tests(test_simulation
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  DISCOVERY_TIMEOUT 10
)

