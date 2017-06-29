//
// Created by fer on 8/06/17.
//

#include "Archer.h"

Archer::Archer(int x, int y, int t) {
    movm = 2;
    health = 3;
    cHealth = 3;
    damage = 2;
    range = 3;
    posX = x;
    posY = y;
    team = t;
    type = archer;
    id = uId;
    uId += 1;
    icon = 'A';
    name = "Archer";
}
