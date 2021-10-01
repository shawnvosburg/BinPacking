cmake_minimum_required(VERSION 3.13)  # CMake version check
project(BinPacking)                   
set(CMAKE_CXX_STANDARD 11)            # Enable c++11 standard

# Adding directories
add_subdirectory(src)
add_subdirectory(tests)