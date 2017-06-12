//
// Created by fer on 8/06/17.
//

#ifndef PROYECTO_ARCHER_H
#define PROYECTO_ARCHER_H

#include "Unit.h"

class Archer : public Unit {
public:
    Archer(int x, int y, int t) : movm(2), health(3), cHealth(3), damage(1), range(3), posX(x), posY(y), team(t) {}

    string typeStats();
};


#endif //PROYECTO_ARCHER_H
