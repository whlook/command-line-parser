cmake_minimum_required(VERSION 3.0)
project(command_line_parser)

set(CMAKE_CXX_STANDARD 11)

add_executable(cat main.cpp command_line_parser.hpp)
