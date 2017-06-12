//
// Created by ivelascog on 9/06/17.
//

#ifndef PROYECTO_ARMY_H
#define PROYECTO_ARMY_H

#include "Unit.h"
#include <list>
#include <vector>

class Army {
    vector<vector<Unit>> units;
public:
    string report();

    void add(Unit unit);

    void remove(Unit unit);

    void massRemove();

    int size();
};


#endif //PROYECTO_ARMY_H
