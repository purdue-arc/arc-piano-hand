cmake_minimum_required(VERSION 3.26)
project(Algos_code_old)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Algos_code_old
        costFunctions.cpp
        Finger.cpp
        FingerState.cpp
        FingerStateAllocationAlgorithm.cpp
        Hand.cpp
        jsonExporter.cpp
        Layer.cpp
        main.cpp
        Node.cpp
        Note.cpp
        pianoHandNamespace.h
        Trellis.cpp
        Viterbi.cpp)
