//
// Created by fer on 13/06/17.
//

#include "TerrainMap.h"

void TerrainMap::loadTerrainMap1() {
    width = 15;
    height = 10;
    tMap = std::vector<std::vector<Terrain *>>((unsigned long) width,
                                               vector<Terrain *>((unsigned long) height, new Plains()));
    setTMap(0, 4, rocks);
    setTMap(1, 5, rocks);
    setTMap(6, 4, rocks);
    setTMap(7, 5, rocks);
    setTMap(8, 4, rocks);
    setTMap(13, 4, rocks);
    setTMap(14, 5, rocks);
}

Terrain *TerrainMap::getTMap(int x, int y) {
    return tMap[x][y];
}

void TerrainMap::setTMap(int x, int y, TerrainTypes type) {
    delete (getTMap(x, y));
    switch (type) {
        case plains:
            tMap[x][y] = new Plains;
        case rocks:
            tMap[x][y] = new Rocks;
        default:
            tMap[x][y] = new Plains;
    }
}