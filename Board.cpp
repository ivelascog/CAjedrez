//
// Created by ivelascog on 8/06/17.
//

#include "Board.h"

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


