//
// Created by fer on 9/06/17.
//

#ifndef PROYECTO_HORSE_H
#define PROYECTO_HORSE_H
#include "Unit.h"

class Horse: Unit {
public:
    Horse(int x, int y, int t)    :movm(6), health(5), cHealth(5), damage(2), range(1), posX(x), posY(y), team(t){}
    string typeStats();
};

#endif //PROYECTO_HORSE_H
