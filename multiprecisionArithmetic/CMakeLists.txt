cmake_minimum_required(VERSION 3.10)

project(multiprecisionArithmetic)

if(UNIX)
  link_libraries(m)
endif(UNIX)

add_executable(add add.c)
add_executable(subtract subtract.c)
add_executable(multiply multiply.c)
add_executable(divide divide.c)

add_executable(test test.c)
add_executable(bigIntTest bigIntTest.c ../others/snprintf.c)

add_executable(performance performance.c)
add_executable(demo demo.c)
add_executable(set set.c)
add_executable(factorial factorial.c)
add_executable(compare compare.c)
add_executable(count count.c)
add_executable(fibonacci fibonacci.c)
