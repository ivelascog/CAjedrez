#include <iostream>
#include "Board.h"//
// Created by ivelascog on 8/06/17.
//

Board::Board() {
    units = new UnitMap();
    terrain = new TerrainMap();
}

void Board::loadMap1() {
    units->loadUnitMap1();
    terrain->loadTerrainMap1();
    height = units->getHeight();
    width = units->getWidth();
}

string Board::printMap(int team) {
    string s = "";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            s += "[";
            if (terrain->getTMap(j, i)->isObstacle()) {
                s += "\033[5;" + to_string(YELLOWBG) + "m \033[0m";
            } else if (units->getUMap(j, i) != nullptr) {
                s += "\033[";
                if (units->getUMap(j, i)->getTeam() == team) {
                    s += to_string(GREEN);
                } else if (units->isAllianceActive() &&
                           units->getAlliance(team) == units->getAlliance(units->getUMap(j, i)->getTeam())) {
                    s += to_string(BLUE);
                } else {
                    s += to_string(RED);
                }
                s += "m";
                s += units->getUMap(j, i)->getIcon();
                s += "\033[" + to_string(RESET) + "m";
            } else {
                s += " ";
            }
            s += "]";
        }
        s += "\n";
    }
    return s;
}


vector<vector<int>> Board::inRange(Unit *u) {
    int ux = u->getPosX();
    int uy = u->getPosY();
    int range = u->getRange();
    vector<vector<int>> map = std::vector<std::vector<int>>((unsigned long) width, vector<int>((unsigned long) height));
    map[ux][uy] = 1;

    if (range == 0) {
        return map;
    }

    range = range + 1;

    for (int l = 1; l < range; l++) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (map[j][i] == l) {
                    if (((j - 1) >= 0) && ((map[j - 1][i]) == 0)) {
                        map[j - 1][i] = (l + 1);
                    }
                    if (((j + 1) < width) && ((map[j + 1][i]) == 0)) {
                        map[j + 1][i] = (l + 1);
                    }
                    if (((i - 1) >= 0) && ((map[j][i - 1]) == 0)) {
                        map[j][i - 1] = (l + 1);
                    }
                    if (((i + 1) < height) && ((map[j][i + 1]) == 0)) {
                        map[j][i + 1] = (l + 1);
                    }
                }
            }
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[j][i] == (range - 1)) {
                if (((j - 1) >= 0) && ((map[j - 1][i]) == 0)) {
                    map[j - 1][i] = range;
                }
                if (((j + 1) < width) && ((map[j + 1][i]) == 0)) {
                    map[j + 1][i] = range;
                }
                if (((i - 1) >= 0) && ((map[j][i - 1]) == 0)) {
                    map[j][i - 1] = range;
                }
                if (((i + 1) < height) && ((map[j][i + 1]) == 0)) {
                    map[j][i + 1] = range;
                }
                if (((j - 1) >= 0) && ((i - 1) >= 0) && ((map[j - 1][i - 1]) == 0)) {
                    map[j - 1][i - 1] = range;
                }
                if (((j - 1) >= 0) && ((i + 1) < height) && ((map[j - 1][i + 1]) == 0)) {
                    map[j - 1][i + 1] = range;
                }
                if (((j + 1) < width) && ((i - 1) >= 0) && ((map[j + 1][i - 1]) == 0)) {
                    map[j + 1][i - 1] = range;
                }
                if (((j + 1) < width) && ((i + 1) < height) && ((map[j + 1][i + 1]) == 0)) {
                    map[j + 1][i + 1] = range;
                }
            }
        }
    }

    if (range >= 6) {
        int n = range;
        int t = (range - 6) / 2;
        for (int q = 0; q <= t; q++) {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if (map[j][i] == (n)) {
                        if (((j - 1) >= 0) && ((map[j - 1][i]) == 0)) {
                            if (ux - (j - 1) < range) {
                                map[j - 1][i] = n + 1;
                            }
                        }
                        if (((j + 1) < width) && ((map[j + 1][i]) == 0)) {
                            if ((j + 1) - ux < range) {
                                map[j + 1][i] = n + 1;
                            }
                        }
                        if (((i - 1) >= 0) && ((map[j][i - 1]) == 0)) {
                            if (uy - (i - 1) < range) {
                                map[j][i - 1] = n + 1;
                            }
                        }
                        if (((i + 1) < height) && ((map[j][i + 1]) == 0)) {
                            if ((i + 1) - uy < range) {
                                map[j][i + 1] = n + 1;
                            }
                        }
                    }
                }
            }
            n++;
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (terrain->getTMap(j, i)->isObstacle()) {
                map[j][i] = -1;
            }
        }
    }

    string s = "";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            s += "[";
            s += to_string(map[j][i]);
            s += "]";
        }
        s += "\n";
    }

    cout << s << endl;

    return map;
}

UnitMap *Board::getUnits() const {
    return units;
}

TerrainMap *Board::getTerrain() const {
    return terrain;
}

vector<vector<bool>> Board::inRangeHostil(Unit *u) {
    vector<vector<bool>> map = std::vector<std::vector<bool>>((unsigned long) width,
                                                              vector<bool>((unsigned long) height, false));
    vector<vector<int>> aux = inRange(u);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (aux[j][i] > 0 && units->getUMap(j, i) != nullptr) {
                map[j][i] = units->isHostile(u, units->getUMap(j, i));
            }
        }
    }
    return map;
}
