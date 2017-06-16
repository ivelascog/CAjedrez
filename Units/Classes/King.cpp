//
// Created by alserrano on 9/06/17.
//

#include "King.h"

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
    icon = 'K';
}