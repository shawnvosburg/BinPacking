cmake_minimum_required(VERSION 3.13)  # CMake version check
project(BinPacking)                   
set(CMAKE_CXX_STANDARD 11)            # Enable c++11 standard

# Creating output folders
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RESULTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/results/)
file(MAKE_DIRECTORY "${CMAKE_RESULTS_DIR}")


# Preprocessor definitions
add_compile_definitions(RESULTS_DIR="${CMAKE_RESULTS_DIR}/")

# Adding directories
add_subdirectory(src)
add_subdirectory(tests)