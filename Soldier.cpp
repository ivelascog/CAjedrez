//
// Created by fer on 9/06/17.
//

#include "Soldier.h"

string Soldier::typeStats() {
    return "Soldier Unit:\nMov: " + to_string(movm) + "\tHealth: " + to_string(health) + "\tDamage: " + to_string(damage) +
           "\tRange: " + to_string(range);
}

Soldier::Soldier(int x, int y, int t) {
    movm = 3;
    health =4;
    cHealth = 4;
    damage = 1;
    range = 1;
    posX = x;
    posY = y;
    team = t;
}

string Soldier::getType() {
    return "Soldier";
}
