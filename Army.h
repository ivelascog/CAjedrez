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
    int availableActions = 0;
    int alliance = -1;
private:
    int size = 0;

public:
    Army(int team);

    //añade ud por puntero; si team difiere, devuelve false y no hace nada
    bool add(Unit *ut);

    //crea y añade ud
    bool add(int x, int y, Types type);

    //sacar ud por id
    bool remove(int id);

    //sacar ud por puntero
    bool remove(Unit *ut);

    //sacar uds muertas
    int massRemove();

    //devuelve numero de uds en army
    int getSize();

    //devuelve puntero a ud por id
    Unit *getUnitByID(int id);

    //string con info completa
    string fullReport();

    //string con info de una clase de UD
    string typeReport(Types uType);

    //reducir acciones
    bool actionDown();

    //resetear acciones
    bool actionReset();

    int getAlliance() const;

    void setAlliance(int alliance);
};


#endif //PROYECTO_ARMY_H
