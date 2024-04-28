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
        Teleporter.cpp
        Teleporter.h
)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/Users/System Manager/CLionProjects/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS audio graphics window system REQUIRED)

include_directories(${SFML_INCLUDE_DIR})
# Link SFML to your project
target_link_libraries(BugsLife sfml-graphics sfml-window sfml-system)