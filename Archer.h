//
// Created by fer on 8/06/17.
//

#ifndef PROYECTO_ARCHER_H
#define PROYECTO_ARCHER_H

#include "Unit.h"

class Archer : public Unit {
public:
    Archer(int x, int y, int t);

    string typeStats();

    string getType();
};


#endif //PROYECTO_ARCHER_H
