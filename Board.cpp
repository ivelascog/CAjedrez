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

vector<vector<int>> Board::accessible(Unit *u) {
    int aux;

    vector<vector<int>> map = std::vector<std::vector<int>>
            ((unsigned long) width, vector<int>((unsigned long) height, 0));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (terrain->getTMap(j, i)->isObstacle() == 1) {
                map[j][i] = -1;
            } else if (units->getUMap(j, i) != nullptr) {
                map[j][i] = -2;
            }
        }
    }

    map[u->getPosX()][u->getPosY()] = u->getMovm() + 1;

    for (int l = (u->getMovm() + 1); l > 1; l--) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (map[j][i] == l) {
                    if (((j - 1) >= 0) && ((map[j - 1][i]) == 0)) {
                        if ((abs(terrain->getTMap(j - 1, i)->getHeight() -
                                 terrain->getTMap(j, i)->getHeight()) < 2) &&
                            terrain->getTMap(j - 1, i)->isHorizontal() &&
                            terrain->getTMap(j, i)->isHorizontal()) {
                            aux = ((l - 1) - terrain->getTMap(j - 1, i)->getPenMov());
                            map[j - 1][i] = max(aux, 1);
                        }
                    }
                    if (((j + 1) < width) && ((map[j + 1][i]) == 0)) {
                        if ((abs(terrain->getTMap(j + 1, i)->getHeight() -
                                 terrain->getTMap(j, i)->getHeight()) < 2) &&
                            terrain->getTMap(j + 1, i)->isHorizontal() &&
                            terrain->getTMap(j, i)->isHorizontal()) {
                            aux = ((l - 1) - terrain->getTMap(j + 1, i)->getPenMov());
                            map[j + 1][i] = max(aux, 1);
                        }
                    }
                    if (((i - 1) >= 0) && ((map[j][i - 1]) == 0)) {
                        if ((abs(terrain->getTMap(j, i - 1)->getHeight() -
                                 terrain->getTMap(j, i)->getHeight()) < 2) &&
                            terrain->getTMap(j, i - 1)->isVertical() &&
                            terrain->getTMap(j, i)->isVertical()) {
                            aux = ((l - 1) - terrain->getTMap(j, i - 1)->getPenMov());
                            map[j][i - 1] = max(aux, 1);
                        }
                    }
                    if (((i + 1) < height) && ((map[j][i + 1]) == 0)) {
                        if ((abs(terrain->getTMap(j, i + 1)->getHeight() -
                                 terrain->getTMap(j, i)->getHeight()) < 2) &&
                            terrain->getTMap(j, i + 1)->isVertical() &&
                            terrain->getTMap(j, i)->isVertical()) {
                            aux = ((l - 1) - terrain->getTMap(j, i + 1)->getPenMov());
                            map[j][i + 1] = max(aux, 1);
                        }
                    }
                }
            }
        }
    }

    return map;
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

    return map;
}

UnitMap *Board::getUnits() const {
    return units;
}

TerrainMap *Board::getTerrain() const {
    return terrain;
}

vector<vector<bool>> Board::inRangeHostile(Unit *u) {
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

vector<vector<bool>> Board::isAccessible(Unit *u) {
    vector<vector<bool>> map = std::vector<std::vector<bool>>((unsigned long) width,
                                                              vector<bool>((unsigned long) height, false));
    vector<vector<int>> aux = accessible(u);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            map[j][i] = (aux[j][i] > 0);
        }
    }
    map[u->getPosX()][u->getPosY()] = false;
    return map;
}

stack<array<int, 2>> Board::walk(Unit *u, int destX, int destY) {
    if (!isAccessible(u)[destX][destY]) {
        throw runtime_error("Not accessible or out of range");
    }

    stack<array<int, 2>> walk;
    vector<vector<int>> map = accessible(u);
    walk.push({destX, destY});
    while (map[destX][destY] <= (u->getMovm())) {
        if (map[destX + 1][destY] > map[destX][destY]) {
            destX = destX + 1;
        } else if (map[destX - 1][destY] > map[destX][destY]) {
            destX = destX - 1;
        } else if (map[destX][destY + 1] > map[destX][destY]) {
            destY = destY + 1;
        } else if (map[destX][destY - 1] > map[destX][destY]) {
            destY = destY - 1;
        }
        walk.push({destX, destY});
    }
    return walk;
}

