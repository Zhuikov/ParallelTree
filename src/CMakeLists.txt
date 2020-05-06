cmake_minimum_required(VERSION 3.5)

project(ParallelTree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

add_subdirectory(benchmark)

add_executable(ParallelTree main.cpp benchmarks.cpp
                BinaryTree.h VectorGeneration.h)

target_link_libraries(ParallelTree benchmark::benchmark)
