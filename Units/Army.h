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
    int size = 0;

public:
    Army(int team);

    int getAvailableActions() const;

    //añade ud por puntero; si team difiere, devuelve false y no hace nada
    bool add(Unit *ut);

    //crea y añade ud
    Unit *add(int x, int y, Types type);

    //sacar ud por id
    Unit *remove(int id);

    //sacar ud por puntero
    Unit *remove(Unit *ut);

    //devuelve numero de uds en army
    int getSize();

    //devuelve puntero a ud por id
    Unit *getUnitByID(int id);

    //string con info completa
    string fullReport();

    //string con info de una clase de UD
    string typeReport(Types uType);

    //reducir acciones
    bool reduceActions();

    //resetear acciones
    bool actionReset();

    int getAlliance() const;

    void setAlliance(int alliance);

    int killAll();

    bool actionsToZero();

    vector<std::list<Unit *>> getRanks();

    virtual ~Army();
};


#endif //PROYECTO_ARMY_H
