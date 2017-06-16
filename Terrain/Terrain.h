//
// Created by fer on 15/06/17.
//

#ifndef PROYECTO_TERRAIN_H
#define PROYECTO_TERRAIN_H

#include <stdlib.h>
#include <string>
#include "TerrainNames.h"

using namespace std;

enum TerrainTypes {
    plains = 0, rocks = 1
};

class Terrain {
protected:
    bool obstacle;
    TerrainTypes type;
    char icon = '?';
public:
    char getIcon() const;

public:
    bool isObstacle() const;

    string terrainStats();
};


#endif //PROYECTO_TERRAIN_H
