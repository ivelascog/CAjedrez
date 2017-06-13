//
// Created by ivelascog on 8/06/17.
//

#ifndef PROYECTO_BOARD_H
#define PROYECTO_BOARD_H

#include <vector>
#include "Unit.h"
#include "Army.h"

enum Population {
    DEFAULT
};

class Board {
private:
    int teams;
    vector<Army> armies;

public:
    void addUnit(Unit u, int team);

    void populate(Population p);
};


#endif //PROYECTO_BOARD_H
