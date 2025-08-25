cmake_minimum_required(VERSION 3.10)

project(multiprecisionArithmetic)

add_executable(add add.c)
add_executable(subtract subtract.c)
add_executable(multiply multiply.c)
add_executable(divide divide.c)

add_executable(test test.c)
add_executable(bigIntTest bigIntTest.c ../others/snprintf.c)

add_executable(performance performance.c)