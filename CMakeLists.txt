cmake_minimum_required(VERSION 3.6)
project(LinearMatrix)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Matrix.cpp Matrix.h Vector.cpp Vector.h LinearEquation.cpp LinearEquation.h)
add_executable(LinearMatrix ${SOURCE_FILES})