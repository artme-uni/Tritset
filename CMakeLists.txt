cmake_minimum_required(VERSION 3.13)
project(Tritset)

set(CMAKE_CXX_STANDARD 14)

add_executable(Tritset main.cpp tritset.cpp tritset.h trit.cpp trit.h)
add_executable(unittest tritset.cpp tritset.h trit.cpp trit.h test.cpp catch.hpp)