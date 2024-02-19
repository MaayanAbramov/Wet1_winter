cmake_minimum_required(VERSION 3.27)
project(Wet1_winter)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Scripts)

add_executable(Wet1_winter
        Scripts/contestant.cpp
        Scripts/contestant.h
        Scripts/country.cpp
        Scripts/country.h
        Scripts/maina1.cpp
        Scripts/Olympicsa1.cpp
        Scripts/Olympicsa1.h
        Scripts/Team.cpp
        Scripts/Team.h
        Scripts/wet1util.h
        AvlTree.h
        test.cpp)
