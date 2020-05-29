cmake_minimum_required(VERSION 3.15)
project(TestC__)

set(CMAKE_CXX_STANDARD 14)

add_executable(TestC__  src/main.cpp src/TestExternal.cpp src/TestExternal.h src/TestRelocate.cpp)