cmake_minimum_required(VERSION 3.22)
project(CompactHamming)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")
add_executable(compact_hamming main.c scaffolding.c compact_hamming.c)
