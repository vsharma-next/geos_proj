cmake_minimum_required(VERSION 3.10)
project(YourProjectName VERSION 1.0)

# Specify C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the src to build libfeanor
add_subdirectory(src)

# Include examples and tests
add_subdirectory(examples)
add_subdirectory(tests)
