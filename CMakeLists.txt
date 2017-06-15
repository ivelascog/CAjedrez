cmake_minimum_required(VERSION 3.7)
project(proyecto)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Unit.h Archer.cpp Archer.h Unit.cpp Soldier.cpp Soldier.h Horse.cpp Horse.h King.cpp King.h
        Army.cpp Army.h UnitList.h Board.cpp Board.h UnitMap.cpp UnitMap.h TerrainMap.cpp TerrainMap.h)
add_executable(proyecto ${SOURCE_FILES})