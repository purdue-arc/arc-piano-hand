cmake_minimum_required(VERSION 3.26)

project(Algos_code)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(Algos_code # Name of the executable
        initial-idea.cpp
        phSpace.h
        Finger.cpp
        Hand.cpp
        test_case_generator.cpp
        Note.cpp
        Viterbi.cpp
        #simple_code.cpp
        #Main.cpp
        bijective_functions.cpp
        input_output.cpp
        finger_state_alloc.cpp          # All sources for the executable
        xml_parsing.cpp
)
