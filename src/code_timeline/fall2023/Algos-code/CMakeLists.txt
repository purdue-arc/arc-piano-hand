cmake_minimum_required(VERSION 3.26)
project(untitled1)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(
        untitled1
        Main.cpp
        phSpace.h
        initial-idea.cpp
        Finger.cpp
        Hand.cpp
        test_case_generator.cpp
        Note.cpp
        Viterbi.cpp
        bijective_functions.cpp
        input_output.cpp
        finger_state_alloc.cpp
        xml_parsing.cpp
)
