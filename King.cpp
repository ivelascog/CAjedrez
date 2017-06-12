//
// Created by alserrano on 9/06/17.
//

#include "King.h"

string King::typeStats() {
    return "King Unit:\nMov: " + to_string(movm) + "\tHealth: " + to_string(health) + "\tDamage: " + to_string(damage) +
           "\tRange: " + to_string(range);
}

King::King(int x, int y, int t) {
    movm = 3;
    health = 10;
    cHealth = 10;
    damage = 4;
    range = 1;
    posX = x;
    posY = y;
    team = t;
    type = king;
    id = uId;
    uId += 1;
}