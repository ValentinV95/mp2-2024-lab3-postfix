file(GLOB hdrs "*.h*" "../include/*.h")
file(GLOB srcs "*.cpp" "../src/*")

add_executable(postfix ${srcs} ${hdrs})
