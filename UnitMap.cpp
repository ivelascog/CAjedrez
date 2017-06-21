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
    defendPos[1] = true;
    posToDefend = vector<vector<array<int, 2>>>((unsigned long) teams);
    posToDefend[1].push_back({4, 6});
    armies = vector<Army *>((unsigned long) teams);
    cemetery = vector<Army *>((unsigned long) teams);
    armies[0] = new Army(0);
    armies[1] = new Army(1);
    cemetery[0] = new Army(0);
    cemetery[1] = new Army(1);

    //Army 0
    addUnit(7, 9, king, 0);
    essentials[0].push_back(getUMap(7, 9));
    addUnit(3, 8, soldier, 0);
    addUnit(5, 8, soldier, 0);
    addUnit(7, 8, soldier, 0);
    addUnit(9, 8, soldier, 0);
    addUnit(11, 8, soldier, 0);
    addUnit(5, 9, archer, 0);
    addUnit(9, 9, archer, 0);
    addUnit(3, 9, horse, 0);
    addUnit(11, 9, horse, 0);

    //Army 1
    addUnit(7, 0, king, 1);
    essentials[1].push_back(getUMap(7, 0));
    addUnit(3, 1, soldier, 1);
    addUnit(5, 1, soldier, 1);
    addUnit(7, 1, soldier, 1);
    addUnit(9, 1, soldier, 1);
    addUnit(11, 1, soldier, 1);
    addUnit(5, 0, archer, 1);
    addUnit(9, 0, archer, 1);
    addUnit(3, 0, horse, 1);
    addUnit(11, 0, horse, 1);
}

UnitMap::~UnitMap() {
    //destruimos uMap
    for (vector<Unit *> v : uMap) {
        //se destruyen Unit en armies (y cemetery)
        v.clear();
    }
    uMap.clear();

    //destruimos armies
    for (Army *a : armies) {
        delete (a);
    }
    armies.clear();

    //destruimos cemetery
    for (Army *a : cemetery) {
        delete (a);
    }
    cemetery.clear();

    //destruimos essentials
    for (vector<Unit *> v : essentials) {
        for (Unit *u : v) {
            delete (u);
        }
        v.clear();
    }
    essentials.clear();

    //destruimos posToDefend
    for (int i = 0; i < posToDefend.size(); i++) {
        posToDefend[i].clear();
    }
    posToDefend.clear();

    lossAfterXTurns.clear();
    turnsToLose.clear();
    defendPos.clear();
    teamActive.clear();
    wipeIsLoss.clear();
    unitIsEssential.clear();
}

bool UnitMap::forceMove(int x1, int y1, int x2, int y2) {
    if (0 <= x1 && 0 <= x2 && 0 <= y1 && 0 <= y2 &&
        x1 < uMap.size() && x2 < uMap.size() && y1 < uMap[0].size() && y2 < uMap[0].size()) {
        if (uMap[x2][y2] == nullptr) {
            uMap[x2][y2] = uMap[x1][y1];
            uMap[x1][y1] = nullptr;
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
        if (uMap[x2][y2] == nullptr && uMap[x1][y1]->getMoveP() > 0) {
            uMap[x2][y2] = uMap[x1][y1];
            uMap[x1][y1] = nullptr;
            uMap[x2][y2]->reduceMovP();
            uMap[x2][y2]->setPos(x2, y2);
            return true;
        }
        return false;
    }
    return false;
}

bool UnitMap::dealDamage(Unit *atta, Unit *defe) {
    if (atta->getTeam() != defe->getTeam() && atta->getAttP() > 0) {
        if (!allianceActive || armies[atta->getTeam()]->getAlliance() != armies[defe->getTeam()]->getAlliance()) {
            defe->takeDamage(atta->getDamage());
            atta->reduceAttP();
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
        teamActive[team] = false;
        return true;
    }

    if (unitIsEssential[team]) {
        for (Unit *ut : essentials[team]) {
            if (ut->isDead()) {
                teamActive[team] = false;
                return true;
            }
        }
    }

    if (lossAfterXTurns[team] && turnsToLose[team] <= currentTurn) {
        teamActive[team] = false;
        return true;
    }

    if (defendPos[team]) {
        for (int i = 0; i < posToDefend[team].size(); i++) {
            auto pos = uMap[posToDefend[team][i][0]][posToDefend[team][i][1]];
            if (pos != nullptr && pos->getTeam() != team) {
                teamActive[team] = false;
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
    teamActive = vector<bool>((unsigned long) teams, true);
}

string UnitMap::showUMap() {
    string s = "";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            s += "[";
            if (uMap[j][i] != nullptr) {
                s += uMap[j][i]->getIcon();
            } else {
                s += " ";
            }
            s += "]";
        }
        s += "\n";
    }
    return s;
}

bool UnitMap::addUnit(int x, int y, Types type, int team) {
    Unit *u = armies[team]->add(x, y, type);
    if (u != nullptr) {
        uMap[x][y] = u;
        return true;
    }
    return false;
}

int UnitMap::massRemove(int team) {
    int bodyCount = 0;
    for (std::list<Unit *> l : armies[team]->getRanks()) {
        for (Unit *u : l) {
            if (u->isDead()) {
                removeUnit(u);
                bodyCount++;
            }
        }
    }
    return bodyCount;
}

int UnitMap::massRemoveComplete() {
    int bodyCount = 0;
    for (int i = 0; i < teams; i++) {
        bodyCount += massRemove(i);
    }
    return bodyCount;
}

bool UnitMap::removeUnit(Unit *ut) {
    uMap[ut->getPosX()][ut->getPosY()] = nullptr;
    cemetery[ut->getTeam()]->add(ut);
    armies[ut->getTeam()]->remove(ut);
    return false;
}

bool UnitMap::isHostile(Unit *u1, Unit *u2) {
    if (allianceActive) {
        return (armies[u1->getTeam()]->getAlliance() != armies[u2->getTeam()]->getAlliance());
    } else {
        return (u1->getTeam() != u2->getTeam());
    }
}

int UnitMap::getHeight() const {
    return height;
}

int UnitMap::getWidth() const {
    return width;
}

bool UnitMap::isAllianceActive() const {
    return allianceActive;
}

int UnitMap::getAlliance(int team) {
    return (armies[team]->getAlliance());
}

bool UnitMap::attack(Unit *att, Unit *def) {
    if (att->getAttP() > 0) {
        bool b = dealDamage(att, def);
        if (b) {
            att->reduceAttP();
            if (att->getMoveP() > 0) {
                att->reduceMovP();
            }
        }
        return b;
    }
    return false;
}
