//
// Created by fer on 13/06/17.
//

#ifndef PROYECTO_TERRAINMAP_H
#define PROYECTO_TERRAINMAP_H


#include "Terrain/TerrainList.h"
#include "Terrain/Terrain.h"
#include <vector>

class TerrainMap {
    vector<vector<Terrain *>> tMap;
    int height;
    int width;
public:
    void loadTerrainMap1();

    Terrain *getTMap(int x, int y);

    void setTMap(int x, int y, TerrainTypes type);

    string showTMap();
};


#endif //PROYECTO_TERRAINMAP_H
