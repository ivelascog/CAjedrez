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

string Army::report() {
    return "Implement";
}

bool Army::add(int x, int y, Types type) {
    switch (type) {
        case king:
            return add(new King(x, y, team));
        case horse:
            return add(new Horse(x, y, team));
        case soldier:
            return add(new Soldier(x, y, team));
        case archer:
            return add(new Archer(x, y, team));
    }
    return false;
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
        size--;
        return true;
    }
    return false;
}

int Army::massRemove() {
    int bodyCount = 0;
    for (std::list<Unit *> r : ranks) {
        for (Unit *ut : r) {
            if (ut->getHealth() <= 0) {
                remove(ut);
                bodyCount++;
            }
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
