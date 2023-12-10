cmake_minimum_required(VERSION 2.8)

include_directories(include gtest)

# BUILD
add_subdirectory(samples)
add_subdirectory(test)
add_subdirectory(gtest)

file(GLOB hdrs "include/*.h")
file(GLOB srcs "src/arithmetic.cpp")

add_library(arithm_lib STATIC "${hdrs}" "${srcs}")