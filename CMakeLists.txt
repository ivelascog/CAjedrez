cmake_minimum_required(VERSION 3.7)
project(proyecto)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Units/Unit.h Units/Classes/Archer.cpp Units/Classes/Archer.h Units/Unit.cpp Units/Classes/Soldier.cpp
        Units/Classes/Soldier.h Units/Classes/Horse.cpp Units/Classes/Horse.h Units/Classes/King.cpp Units/Classes/King.h
        Units/Army.cpp Units/Army.h Units/UnitList.h Board.cpp Board.h UnitMap.cpp UnitMap.h TerrainMap.cpp TerrainMap.h
        Terrain/Terrain.cpp Terrain/Terrain.h Terrain/TerrainList.h Terrain/Types/Plains.cpp Terrain/Types/Plains.h
        Terrain/Types/Rocks.cpp Terrain/Types/Rocks.h Units/UnitNames.h Terrain/TerrainNames.h multiplayer.cpp multiplayer.h)
add_executable(proyecto ${SOURCE_FILES})