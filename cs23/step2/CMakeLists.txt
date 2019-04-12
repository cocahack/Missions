cmake_minimum_required(VERSION 3.10)
project(step2)

set(CMAKE_CXX_STANDARD 17)

add_executable(step2 main.cpp custom_memory.h constants.h custom_memory.cpp custom_cpu.h alu.h register.h custom_cpu.cpp util.h)