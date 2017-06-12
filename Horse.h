//
// Created by fer on 9/06/17.
//

#ifndef PROYECTO_HORSE_H
#define PROYECTO_HORSE_H

#include "Unit.h"

class Horse : public Unit {
public:
    Horse(int x, int y, int t);

    string typeStats();
};

#endif //PROYECTO_HORSE_H
