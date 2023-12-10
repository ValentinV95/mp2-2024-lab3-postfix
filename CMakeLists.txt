cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 20)

include_directories(include gtest)

# BUILD
add_subdirectory(samples)
add_subdirectory(test)
add_subdirectory(gtest)