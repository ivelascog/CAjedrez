//
// Created by fer on 13/06/17.
//

#include <stdexcept>
#include "UnitMap.h"

void UnitMap::loadUnitMap1() {
    width = 15;
    height = 10;
    uMap = std::vector<std::vector<Unit *>>((unsigned long) width, vector<Unit *>((unsigned long) height));
    teams = 2;
    currentTurn = 0;
    condInit();
    unitIsEssential = vector<bool>((unsigned long) teams, true);
    essentials = vector<vector<Unit *>>((unsigned long) teams);
    armies = vector<Army *>((unsigned long) teams);
    armies[0] = new Army(0);
    armies[1] = new Army(1);

    //Army 0
    armies[0]->add(7, 9, king);
    essentials[0].push_back(getUMap(7, 9));
    armies[0]->add(3, 8, soldier);
    armies[0]->add(5, 8, soldier);
    armies[0]->add(7, 8, soldier);
    armies[0]->add(9, 8, soldier);
    armies[0]->add(11, 8, soldier);
    armies[0]->add(5, 9, archer);
    armies[0]->add(9, 9, archer);
    armies[0]->add(3, 9, horse);
    armies[0]->add(11, 9, horse);

    //Army 1
    armies[1]->add(7, 0, king);
    essentials[1].push_back(getUMap(7, 0));
    armies[1]->add(3, 1, soldier);
    armies[1]->add(5, 1, soldier);
    armies[1]->add(7, 1, soldier);
    armies[1]->add(9, 1, soldier);
    armies[1]->add(11, 1, soldier);
    armies[1]->add(5, 0, archer);
    armies[1]->add(9, 0, archer);
    armies[1]->add(3, 0, horse);
    armies[1]->add(11, 0, horse);
}

bool UnitMap::forceMove(int x1, int y1, int x2, int y2) {
    if (0 <= x1 && 0 <= x2 && 0 <= y1 && 0 <= y2 &&
        x1 < uMap.size() && x2 < uMap.size() && y1 < uMap[0].size() && y2 < uMap[0].size()) {
        if (uMap[x2][y2] == NULL) {
            uMap[x2][y2] = uMap[x1][y1];
            uMap[x1][y1] = NULL;
            uMap[x2][y2]->setPos(x2, y2);
            return true;
        }
        return false;
    }
    return false;
}

bool UnitMap::move(int x1, int y1, int x2, int y2) {
    if (0 <= x1 && 0 <= x2 && 0 <= y1 && 0 <= y2 &&
        x1 < uMap.size() && x2 < uMap.size() && y1 < uMap[0].size() && y2 < uMap[0].size()) {
        if (uMap[x2][y2] == NULL && uMap[x1][y1]->getMoveP() > 0) {
            uMap[x2][y2] = uMap[x1][y1];
            uMap[x1][y1] = NULL;
            uMap[x2][y2]->reduceMovP();
            uMap[x2][y2]->setPos(x2, y2);
            return true;
        }
        return false;
    }
    return false;
}

bool UnitMap::dealDamage(Unit *atta, Unit *defe) {
    Unit att = *atta;
    Unit def = *defe;
    if (att.getTeam() != def.getTeam() && att.getAttP() > 0) {
        if (!allianceActive || armies[att.getTeam()]->getAlliance() != armies[def.getTeam()]->getAlliance()) {
            def.takeDamage(att.getDamage());
            att.reduceAttP();
            return true;
        }
        return false;
    }
    return false;
}

bool UnitMap::checkLoss(int team) {

    if (team >= teams) {
        return false;
    }

    if (wipeIsLoss[team] && armies[team]->getSize() <= 0) {
        return true;
    }

    if (unitIsEssential[team]) {
        for (Unit *ut : essentials[team]) {
            if (ut->isDead()) {
                return true;
            }
        }
    }

    if (lossAfterXTurns[team] && turnsToLose[team] <= currentTurn) {
        return true;
    }

    if (defendPos[team]) {
        for (int i = 0; i < posToDefend[team].size(); i++) {
            auto pos = uMap[posToDefend[team][i][0]][posToDefend[team][i][1]];
            if (pos != NULL && pos->getTeam() != team) {
                return true;
            }
        }
    }

    return false;
}

void UnitMap::advanceTurn() {
    currentTurn++;
}

int UnitMap::getCurrentTurn() const {
    return currentTurn;
}

int UnitMap::checkWin() {
    int countAlive = 0;
    int teamAlive = -1;

    if (allianceActive) {
        for (int i = 0; i < teams; i++) {
            if (teamActive[i]) {
                if (teamAlive != armies[i]->getAlliance()) {
                    teamAlive = armies[i]->getAlliance();
                    countAlive++;
                }
            }
        }
    } else {
        for (int i = 0; i < teams; i++) {
            if (teamActive[i]) {
                teamAlive = i;
                countAlive++;
            }
        }
    }

    if (countAlive == 1) {
        return teamAlive;
    }

    return -1;
}

Army *UnitMap::getArmies(int n) {
    if (n < teams) {
        return armies[n];
    }
    throw std::runtime_error("Index out of bounds exception");
}


Unit *UnitMap::getUMap(int x, int y) {
    if (x < width && y < height) {
        return uMap[x][y];
    }
    throw std::runtime_error("Index out of bounds exception");
}

bool UnitMap::getTeamActive(int team) {
    if (team < teams) {
        return teamActive[team];
    }
    throw std::runtime_error("Index out of bounds exception");
}

void UnitMap::condInit() {
    wipeIsLoss = vector<bool>((unsigned long) teams, true);
    unitIsEssential = vector<bool>((unsigned long) teams, false);
    lossAfterXTurns = vector<bool>((unsigned long) teams, false);
    defendPos = vector<bool>((unsigned long) teams, false);
}
