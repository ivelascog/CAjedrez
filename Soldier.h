//
// Created by fer on 9/06/17.
//

#ifndef PROYECTO_SOLDIER_H
#define PROYECTO_SOLDIER_H
#include "Unit.h"

class Soldier: Unit {
public:
    Soldier(int x, int y, int t)    :movm(3), health(4), cHealth(4), damage(1), range(1), posX(x), posY(y), team(t){}
    string typeStats();
};


#endif //PROYECTO_SOLDIER_H
