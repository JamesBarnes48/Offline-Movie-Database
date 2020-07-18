cmake_minimum_required(VERSION 3.15)
project(OMDB)

set(CMAKE_CXX_STANDARD 14)

add_executable(OMDB main.cpp Movie.cpp Movie.h MovieDatabase.cpp MovieDatabase.h)