cmake_minimum_required(VERSION 3.28)
project(PostmanAlgorithm)

set(CMAKE_CXX_STANDARD 11)

add_executable(PostmanAlgorithm main.cpp
        PostmanProblemSolver.cpp
        PostmanProblemSolver.h
        path.h)
