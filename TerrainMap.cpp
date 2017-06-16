//
// Created by fer on 13/06/17.
//

#include <stdexcept>
#include "TerrainMap.h"

void TerrainMap::loadTerrainMap1() {
    width = 15;
    height = 10;
    tMap = std::vector<std::vector<Terrain *>>((unsigned long) width,
                                               vector<Terrain *>((unsigned long) height));
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            tMap[j][i] = new Plains();
        }
    }

    setTMap(0, 4, rocks);
    setTMap(1, 5, rocks);
    setTMap(6, 4, rocks);
    setTMap(7, 5, rocks);
    setTMap(8, 4, rocks);
    setTMap(13, 4, rocks);
    setTMap(14, 5, rocks);
}

Terrain *TerrainMap::getTMap(int x, int y) {
    if (x < width && y < height) {
        return tMap[y][x];
    }
    throw std::runtime_error("Index out of bounds exception");
}

void TerrainMap::setTMap(int x, int y, TerrainTypes type) {
    if (x < width && y < height) {
        delete (getTMap(x, y));
        switch (type) {
            case plains:
                tMap[y][x] = new Plains();
                break;
            case rocks:
                tMap[y][x] = new Rocks();
                break;
            default:
                tMap[y][x] = new Plains();
                break;
        }
    } else {
        throw std::runtime_error("Index out of bounds exception");
    }
}

string TerrainMap::showTMap() {
    string s = "";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            s += "[";
            s += tMap[i][j]->getIcon();
            s += "]";
        }
        s += "\n";
    }
    return s;
}
