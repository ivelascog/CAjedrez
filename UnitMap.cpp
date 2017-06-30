//
// Created by fer on 13/06/17.
//

#include <stdexcept>
#include "UnitMap.h"

UnitMap::~UnitMap() {
    //destruimos uMap
    for (vector<Unit *> v : uMap) {
        //se destruyen Unit en armies (y cemetery)
        v.clear();
    }
    uMap.clear();

    //destruimos armies
    for (Army *a : armies) {
        //delete (a);
    }
    armies.clear();

    //destruimos cemetery
    for (Army *a : cemetery) {
        //delete (a);
    }
    cemetery.clear();

    //destruimos essentials
    for (vector<Unit *> v : essentials) {
        for (Unit *u : v) {
            // delete (u);
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
        armies[team]->killAll();
        massRemove(team);
        return true;
    }

    if (unitIsEssential[team]) {
        for (Unit *ut : essentials[team]) {
            if (ut->isDead()) {
                teamActive[team] = false;
                armies[team]->killAll();
                massRemove(team);
                return true;
            }
        }
    }

    if (defendPos[team]) {
        for (int i = 0; i < posToDefend[team].size(); i++) {
            auto pos = uMap[posToDefend[team][i][0]][posToDefend[team][i][1]];
            if (pos != nullptr && pos->getTeam() != team) {
                teamActive[team] = false;
                armies[team]->killAll();
                massRemove(team);
                return true;
            }
        }
    }

    return false;
}

void UnitMap::checkTurnLoss() {
    for (int team = 0; team < teams; team++) {
        if (lossAfterXTurns[team] && turnsToLose[team] <= currentTurn) {
            teamActive[team] = false;
            armies[team]->killAll();
            massRemove(team);
        }
    }
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

    checkLossAll();

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

    if (countAlive == 0) {
        throw runtime_error("Error: all teams have lost");
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
    armies = vector<Army *>((unsigned long) teams);
    cemetery = vector<Army *>((unsigned long) teams);
    for (int i = 0; i < teams; i++) {
        armies[i] = new Army(i);
        cemetery[i] = new Army(i);
    }
    currentTurn = 0;
    wipeIsLoss = vector<bool>((unsigned long) teams, true);
    unitIsEssential = vector<bool>((unsigned long) teams, false);
    lossAfterXTurns = vector<bool>((unsigned long) teams, false);
    defendPos = vector<bool>((unsigned long) teams, false);
    teamActive = vector<bool>((unsigned long) teams, true);
    essentials = vector<vector<Unit *>>((unsigned long) teams);
    posToDefend = vector<vector<array<int, 2>>>((unsigned long) teams);
    turnsToLose = vector<int>((unsigned long) teams);
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
    return isHostile(u1->getTeam(), u2->getTeam());
}

bool UnitMap::isHostile(int team1, int team2) {
    if (allianceActive) {
        return (armies[team1]->getAlliance() != armies[team2]->getAlliance());
    } else {
        return (team1 != team2);
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

int UnitMap::getTeams() const {
    return teams;
}

void UnitMap::checkLossAll() {
    for (int i = 0; i < teams; i++) {
        checkLoss(i);
    }
}

string UnitMap::completeMiniReport() {
    string s = "";
    for (Army *a : armies) {
        s += a->fullMiniReport();
    }
    return s;
}

string UnitMap::consultUnitByID(int id) {
    for (Army *a : armies) {
        if (a->getUnitByID(id) != nullptr)
            return a->getUnitByID(id)->report() + "\n" + a->getUnitByID(id)->typeStats() + "\n";
    }
    return "No such unit.";
}

string UnitMap::placeboAttack(Unit *att, Unit *def) {
    return def->getName() + "(ID: " + to_string(def->getId()) + ")\t" + to_string(def->getCHealth()) +
           "/" + to_string(def->getHealth()) + " -> " + to_string(max((def->getCHealth() - att->getDamage()), 0)) +
           "/" + to_string(def->getHealth());
}

Unit *UnitMap::getUnitByID(int id) {
    for (Army *a : armies) {
        if (a->getUnitByID(id) != nullptr)
            return a->getUnitByID(id);
    }
    return nullptr;
}

void UnitMap::initMap(int w, int h) {
    width = w;
    height = h;
    uMap = std::vector<std::vector<Unit *>>((unsigned long) width, vector<Unit *>((unsigned long) height));
}

void UnitMap::addEssential(Unit *u, int team) {
    if (!unitIsEssential[team]) {
        unitIsEssential[team] = true;
    }
    essentials[team].push_back(u);
}

void UnitMap::addPosToDefend(int x, int y, int team) {
    if (!defendPos[team]) {
        defendPos[team] = true;
    }
    posToDefend[team].push_back({x, y});
}

void UnitMap::wipeIsNotLoss(int team) {
    wipeIsLoss[team] = false;
};

void UnitMap::turnLimit(int turn, int team) {
    if (!lossAfterXTurns[team]) {
        lossAfterXTurns[team] = true;
    }
    turnsToLose[team] = turn;
}

void UnitMap::addToAlliance(int team, int alliance) {
    allianceActive = true;
    armies[team]->setAlliance(alliance);
};

void UnitMap::loadUnitMap1() {
    initMap(15, 10);
    teams = 2;
    condInit();

    //Army 0
    addUnit(7, 9, king, 0);
    addEssential(getUMap(7, 9), 0);
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
    addEssential(getUMap(7, 0), 1);
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

void UnitMap::loadUnitMapCastleAssault() {
    initMap(25, 15);
    teams = 3;
    condInit();

    addToAlliance(0, 0);
    addToAlliance(1, 1);
    addToAlliance(2, 1);

    addPosToDefend(12, 2, 0);
    getArmies(0)->setActionHandicap(1);
    turnLimit(10, 1);
    turnLimit(10, 2);

    addUnit(12, 5, king, 0);
    addEssential(getUMap(12, 5), 0);
    addUnit(12, 8, horse, 0);
    addUnit(11, 8, horse, 0);
    addUnit(10, 8, horse, 0);
    addUnit(11, 9, soldier, 0);
    addUnit(12, 9, soldier, 0);
    addUnit(13, 9, soldier, 0);
    addUnit(14, 9, soldier, 0);
    addUnit(10, 9, soldier, 0);
    addUnit(7, 5, soldier, 0);
    addUnit(17, 5, soldier, 0);
    addUnit(16, 8, archer, 0);
    addUnit(8, 8, archer, 0);
    addUnit(15, 6, archer, 0);
    addUnit(9, 6, archer, 0);

    addUnit(1, 9, horse, 1);
    addUnit(2, 10, horse, 1);
    addUnit(3, 11, horse, 1);
    addUnit(4, 12, horse, 1);
    addUnit(4, 4, soldier, 1);
    addUnit(4, 6, soldier, 1);
    addUnit(9, 12, soldier, 1);
    addUnit(11, 12, soldier, 1);
    addUnit(10, 13, archer, 1);
    addUnit(3, 5, archer, 1);

    addUnit(23, 9, horse, 2);
    addUnit(22, 10, horse, 2);
    addUnit(21, 11, horse, 2);
    addUnit(20, 12, horse, 2);
    addUnit(20, 4, soldier, 2);
    addUnit(20, 6, soldier, 2);
    addUnit(13, 12, soldier, 2);
    addUnit(15, 12, soldier, 2);
    addUnit(14, 13, archer, 2);
    addUnit(21, 5, archer, 2);
}

int UnitMap::isPosToDefend(int x, int y, int team) {
    for (int j = 0; j < posToDefend.size(); j++) {
        for (int i = 0; i < posToDefend[j].size(); i++) {
            if (posToDefend[j][i][0] == x && posToDefend[j][i][1] == y) {
                if (j == team) {
                    //to defend return 1
                    return 1;
                } else if (isHostile(team, j)) {
                    //to attack return 2
                    return 2;
                } else {
                    //ally return 3
                    return 3;
                }
            }
        }
    }
    //else return 0
    return 0;
}