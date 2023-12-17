set(target postfix_test)

file(GLOB test_srcs "*.cpp")

add_executable(${target} ${test_srcs})
target_link_libraries(${target} gtest arithm_lib)
