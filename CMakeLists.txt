cmake_minimum_required(VERSION 3.14)
cmake_policy(SET CMP0135 NEW)

project(MountyHall VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Suppress deprecated Python warnings 
add_compile_options(-Wno-deprecated-declarations)

# ---- Find Python and NumPy ----
find_package(Python3 REQUIRED COMPONENTS Interpreter Development NumPy)

# ---- Include directories ----
include_directories(
  include 
  external
  ${Python3_INCLUDE_DIRS}
  ${Python3_NumPy_INCLUDE_DIRS}
)

# ---- Main app ----
add_executable(MountyHall
  src/main.cpp
  src/plot.cpp
  src/simulation.cpp
)

target_link_libraries(MountyHall PRIVATE ${Python3_LIBRARIES})

# ---- GoogleTest setup ----
include(FetchContent)

# Prevent timestamp warning
set(FETCHCONTENT_DOWNLOAD_EXTRACT_TIMESTAMP TRUE)  

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

# ---- Unit Test: test_utils ----
add_executable(test_utils
  tests/test_utils.cpp
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

# ---- Unit Test: test_simulation ----
add_executable(test_simulation
  tests/test_simulation.cpp
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

