//
// Created by ivelascog on 9/06/17.
//

#ifndef PROYECTO_ARMY_H
#define PROYECTO_ARMY_H

#include "Unit.h"
#include <list>

class Army {
    list <list<Unit>> units;
public:
    string report();

    void add(Unit unit);

    void remove(Unit unit);

    void massRemove();
};


#endif //PROYECTO_ARMY_H
