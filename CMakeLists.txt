cmake_minimum_required(VERSION 3.27)
project(BugsLife)

set(CMAKE_CXX_STANDARD 17)

add_executable(BugsLife main.cpp
        Bug.cpp
        Bug.h
        Hopper.cpp
        Hopper.h
        Crawler.cpp
        Crawler.h
        Board.cpp
        Board.h
)
