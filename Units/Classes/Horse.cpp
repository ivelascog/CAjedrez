//
// Created by fer on 9/06/17.
//

#include "Horse.h"

Horse::Horse(int x, int y, int t) {
    movm = 6;
    health = 5;
    damage = 2;
    range = 1;
    posX = x;
    posY = y;
    team = t;
    cHealth = 5;
    type = horse;
    id = uId;
    uId += 1;
    icon = 'H';
    maxMoveP = 2;
    name = "Knight";
}
