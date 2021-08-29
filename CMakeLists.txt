cmake_minimum_required(VERSION 3.19)

# set the project name
project(union_find)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(union_find main.cpp Helper.h)