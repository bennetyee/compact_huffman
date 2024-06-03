cmake_minimum_required(VERSION 3.22)
project(CompactHuffman)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")
add_executable(compact_huffman main.c scaffolding.c compact_huffman.c)
