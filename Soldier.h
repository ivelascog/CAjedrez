//
// Created by fer on 9/06/17.
//

#ifndef PROYECTO_SOLDIER_H
#define PROYECTO_SOLDIER_H

#include "Unit.h"

class Soldier : public Unit {
public:
    Soldier(int x, int y, int t);

    //devuelve stats de la clase (no ud)
    string typeStats();
};


#endif //PROYECTO_SOLDIER_H
