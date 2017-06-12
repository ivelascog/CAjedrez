//
// Created by fer on 9/06/17.
//

#ifndef PROYECTO_SOLDIER_H
#define PROYECTO_SOLDIER_H

#include "Unit.h"

class Soldier : public Unit {
public:
    Soldier(int x, int y, int t);

    string typeStats();

    string getType();
};


#endif //PROYECTO_SOLDIER_H
