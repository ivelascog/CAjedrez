//
// Created by alserrano on 9/06/17.
//

#ifndef PROYECTO_KING_H
#define PROYECTO_KING_H

#include "Unit.h"

class King : Unit {
public:
    King(int x, int y, int t) : movm(3), health(10), cHealth(10), damage(4), range(1), posX(x), posY(y), team(t) {}

    string typeStats();
};


#endif //PROYECTO_KING_H
