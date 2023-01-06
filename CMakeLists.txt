cmake_minimum_required(VERSION 3.24)
project(minesweeper C)

set(CMAKE_C_STANDARD 11)

add_executable(minesweeper main.c Minesweeper.h)
