cmake_minimum_required(VERSION 3.0)
project(WinterAvlTree)

set(CMAKE_CXX_STANDARD 14)

add_executable(WinterAvlTree maina1.cpp AvlTree.h Team.h Team.cpp Contestant.cpp Contestant.h Country.h Country.cpp
        Olympicsa1.cpp Olympicsa1.h wet1util.h Country_Key.h Contestant_Key.h Team_Key.h)
