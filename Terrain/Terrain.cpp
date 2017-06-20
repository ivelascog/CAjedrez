//
// Created by fer on 15/06/17.
//

#include "Terrain.h"

bool Terrain::isObstacle() const {
    return obstacle;
}

string Terrain::terrainStats() {
    string s = terrainNames[type] + ":\n";
    if (obstacle) {
        s += "Not transitable";
    } else {
        s += "Transitable";
    }
    return s;
}

char Terrain::getIcon() {
    return icon;
}

int Terrain::getPenMov() const {
    return penMov;
}

int Terrain::getHeight() const {
    return height;
}

bool Terrain::isHorizontal() const {
    return horizontal;
}

bool Terrain::isVertical() const {
    return vertical;
}
