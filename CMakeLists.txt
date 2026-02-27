cmake_minimum_required(VERSION 3.10)
project(CommodityEngine)

set(CMAKE_CXX_STANDARD 17)

# We are NO LONGER finding OpenMP
find_package(pybind11 REQUIRED)

include_directories(include)

# Build the Python Module with standard linking
pybind11_add_module(gs_pricer src/bindings.cpp src/MonteCarloEngine.cpp)

# Build the Unit Tests without OpenMP
add_executable(UnitTests src/tests.cpp src/MonteCarloEngine.cpp)