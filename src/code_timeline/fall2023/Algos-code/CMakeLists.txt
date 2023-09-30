cmake_minimum_required(VERSION 3.26)
project(Algos_code)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Algos_code
        initial-idea.cpp
        phSpace.h
        Finger.cpp
        Hand.cpp
        test_case_generator.cpp
        Note.cpp
        Viterbi_extensible.cpp)
