//
// Created by fer on 8/06/17.
//

#include "Archer.h"

string Archer::typeStats() {
    return "Archer Unit:\nMov: " + to_string(movm) + "\tHealth: " + to_string(health) + "\tDamage: " +
           to_string(damage) +
           "\tRange: " + to_string(range);
}

Archer::Archer(int x, int y, int t) {
    movm = 2;
    health = 3;
    cHealth = 3;
    damage = 1;
    range = 3;
    posX = x;
    posY = y;
    team = t;
    type = archer;
    id = uId;
    uId += 1;
}
