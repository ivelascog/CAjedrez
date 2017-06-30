//
// Created by fer on 13/06/17.
//

#include <stdexcept>
#include "TerrainMap.h"

void TerrainMap::loadTerrainCastleAssault() {
    width = 25;
    height = 15;
    tMap = std::vector<std::vector<Terrain *>>((unsigned long) width,
                                               vector<Terrain *>((unsigned long) height));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            tMap[j][i] = new Plains();
        }
    }

    setTMap(6, 0, rocks);
    setTMap(18, 0, rocks);
    setTMap(6, 1, rocks);
    setTMap(18, 1, rocks);
    setTMap(6, 2, rocks);
    setTMap(18, 2, rocks);
    setTMap(6, 3, rocks);
    setTMap(18, 3, rocks);
    setTMap(6, 4, rocks);
    setTMap(18, 4, rocks);
    setTMap(6, 6, rocks);
    setTMap(18, 6, rocks);
    setTMap(6, 7, rocks);
    setTMap(18, 7, rocks);
    setTMap(6, 8, rocks);
    setTMap(18, 8, rocks);
    setTMap(6, 9, rocks);
    setTMap(18, 9, rocks);
    setTMap(6, 10, rocks);
    setTMap(18, 10, rocks);
    setTMap(7, 10, rocks);
    setTMap(8, 10, rocks);
    setTMap(9, 10, rocks);
    setTMap(10, 10, rocks);
    setTMap(14, 10, rocks);
    setTMap(15, 10, rocks);
    setTMap(16, 10, rocks);
    setTMap(17, 10, rocks);
}

void TerrainMap::loadTerrainMap1() {
    width = 15;
    height = 10;
    tMap = std::vector<std::vector<Terrain *>>((unsigned long) width,
                                               vector<Terrain *>((unsigned long) height));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            tMap[j][i] = new Plains();
        }
    }

    setTMap(2, 4, rocks);
    setTMap(0, 5, rocks);
    setTMap(1, 5, rocks);
    setTMap(2, 5, rocks);
    setTMap(6, 4, rocks);
    setTMap(6, 5, rocks);
    setTMap(6, 6, rocks);
    setTMap(8, 3, rocks);
    setTMap(8, 4, rocks);
    setTMap(8, 5, rocks);
    setTMap(0, 0, rocks);
    setTMap(0, 9, rocks);
    setTMap(14, 0, rocks);
    setTMap(14, 9, rocks);
    setTMap(12, 5, rocks);
    setTMap(14, 4, rocks);
    setTMap(13, 4, rocks);
    setTMap(12, 4, rocks);
}

Terrain *TerrainMap::getTMap(int x, int y) {
    if (x < width && y < height) {
        return tMap[x][y];
    }
    throw std::runtime_error("Index out of bounds exception");
}

void TerrainMap::setTMap(int x, int y, TerrainTypes type) {
    if (x < width && y < height) {
        delete (getTMap(x, y));
        switch (type) {
            case plains:
                tMap[x][y] = new Plains();
                break;
            case rocks:
                tMap[x][y] = new Rocks();
                break;
            default:
                tMap[x][y] = new Plains();
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

TerrainMap::~TerrainMap() {
    //destruimos tMap
    for (vector<Terrain *> v : tMap) {
        for (Terrain *t : v) {
            delete (t);
        }
        //v.clear();
    }
    tMap.clear();
}
