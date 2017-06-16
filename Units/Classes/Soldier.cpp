//
// Created by fer on 9/06/17.
//

#include "Soldier.h"

Soldier::Soldier(int x, int y, int t) {
    movm = 3;
    health = 4;
    cHealth = 4;
    damage = 1;
    range = 1;
    posX = x;
    posY = y;
    team = t;
    type = soldier;
    id = uId;
    uId += 1;
    icon = 'S';
}
