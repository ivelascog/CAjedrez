cmake_minimum_required(VERSION 3.7)
project(proyecto)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Unit.h Board.cpp Board.h Archer.cpp Archer.h Unit.cpp Soldier.cpp Soldier.h Horse.cpp Horse.h King.cpp King.h Army.cpp Army.h)
add_executable(proyecto ${SOURCE_FILES})