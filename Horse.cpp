//
// Created by fer on 9/06/17.
//

#include "Horse.h"

string Horse::typeStats() {
    return "Horse Unit:\nMov: " + to_string(movm) + "\tHealth: " + to_string(health) + "\tDamage: " + to_string(damage) +
           "\tRange: " + to_string(range);
}

Horse::Horse(int x, int y, int t) {
    movm = 6;
    health = 5;
    damage = 2;
    range = 1;
    posX = x;
    posY = y;
    team = t;
    cHealth = 5;
}

string Horse::getType() {
    return "Horse";
}
