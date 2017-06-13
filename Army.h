//
// Created by ivelascog on 9/06/17.
//

#ifndef PROYECTO_ARMY_H
#define PROYECTO_ARMY_H

#include "Unit.h"
#include <vector>
#include <list>

class Army {
    vector<std::list<Unit *>> ranks;
    int team;
    int size = 0;

public:
    Army(int team);

    string report();

    bool add(Unit *ut);

    bool add(int x, int y, Types type);

    bool remove(int id);

    bool remove(Unit *ut);

    int massRemove();

    int getSize();

    Unit *getUnitByID(int id);
};


#endif //PROYECTO_ARMY_H
