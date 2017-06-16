//
// Created by ivelascog on 9/06/17.
//

#include "Army.h"
#include "UnitList.h"

Army::Army(int team) {
    for (int i = 0; i < NUMUNITS; i++) {
        ranks.push_back(*new std::list<Unit *>);
    }
    this->team = team;
}

string Army::fullReport() {
    string s = "Report of army " + to_string(team) + ":\n";
    for (int t = 0; t < NUMUNITS; t++) {
        if (!ranks[t].empty()) {
            s += "\n" + typeReport(Types(t));
        }
    }
    s += "\n";
    return s;
}


string Army::typeReport(Types uType) {
    string s = "\t\t//" + unitNames[uType] + "//\n";
    for (Unit *ut : ranks[uType]) {
        s += "\t" + ut->report() + "\n";
    }
    return s;
}

Unit *Army::add(int x, int y, Types type) {
    Unit *u;
    switch (type) {
        case king:
            u = new King(x, y, team);
            add(u);
            return u;
        case horse:
            u = new Horse(x, y, team);
            add(u);
            return u;
        case soldier:
            u = new Soldier(x, y, team);
            add(u);
            return u;
        case archer:
            u = new Archer(x, y, team);
            add(u);
            return u;
        default:
            return NULL;
    }
}

bool Army::add(Unit *ut) {
    if (ut->getTeam() == team) {
        ranks[ut->getType()].push_back(ut);
        size++;
        return true;
    }
    return false;
}

bool Army::remove(int id) {
    return remove(getUnitByID(id));
}

bool Army::remove(Unit *ut) {
    if (ut != NULL) {
        ranks[ut->getType()].remove(ut);
        delete (ut);
        size--;
        return true;
    }
    return false;
}

int Army::massRemove() {
    int bodyCount = 0;
    for (std::list<Unit *> r : ranks) {
        for (Unit *ut : r) {
            if (ut->isDead()) {
                remove(ut);
                bodyCount++;
            }
        }
    }
    return bodyCount;
}

int Army::killAll() {
    int bodyCount = 0;
    for (std::list<Unit *> r : ranks) {
        for (Unit *ut : r) {
            ut->setCHealth(0);
            bodyCount++;
        }
    }
    return bodyCount;
}

int Army::getSize() {
    return size;
}

Unit *Army::getUnitByID(int id) {
    for (std::list<Unit *> r : ranks) {
        for (Unit *ut : r) {
            if (ut->getId() == id)
                return ut;
        }
    }
    return NULL;
}

bool Army::actionDown() {
    if (availableActions > 0) {
        availableActions--;
        return true;
    }
    return false;
}

int Army::getAlliance() const {
    return alliance;
}

void Army::setAlliance(int alliance) {
    Army::alliance = alliance;
}

bool Army::actionReset() {
    availableActions = size / 3;
    for (std::list<Unit *> r : ranks) {
        for (Unit *ut : r) {
            ut->resetAP();
        }
    }
}

bool Army::actionsToZero() {
    availableActions = 0;
    for (std::list<Unit *> r : ranks) {
        for (Unit *ut : r) {
            ut->setAttP(0);
            ut->setMoveP(0);
        }
    }
}