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

char Terrain::getIcon() const {
    return icon;
}
