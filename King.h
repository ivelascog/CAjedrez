//
// Created by alserrano on 9/06/17.
//

#ifndef PROYECTO_KING_H
#define PROYECTO_KING_H

#include "Unit.h"

class King : public Unit {
public:
    King(int x, int y, int t);

    string typeStats();

    string getType();
};


#endif //PROYECTO_KING_H
