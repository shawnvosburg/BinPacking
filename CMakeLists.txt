cmake_minimum_required(VERSION 3.13)  # CMake version check
project(BinPacking)                   
set(CMAKE_CXX_STANDARD 11)            # Enable c++11 standard
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Preprocessor definitions
add_compile_definitions(RESULTS_DIR="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/results/")
file(MAKE_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/results/")

# Adding directories
add_subdirectory(src)
add_subdirectory(tests)