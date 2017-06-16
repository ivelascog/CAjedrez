//
// Created by fer on 13/06/17.
//

#ifndef PROYECTO_UNITMAP_H
#define PROYECTO_UNITMAP_H

#include "Units/Unit.h"
#include "Units/Army.h"

class UnitMap {
    vector <vector<Unit *>> uMap;
    vector<Army *> armies;
    vector<bool> teamActive;
    int height;
    int width;
    int teams;
    bool allianceActive = false;
    int currentTurn;

    //losscons
    vector<bool> wipeIsLoss;

    vector<bool> unitIsEssential;
    vector <vector<Unit *>> essentials;

    vector<bool> lossAfterXTurns;
    vector<int> turnsToLose;

    vector<bool> defendPos;
    vector <vector<int[2]>> posToDefend;

    //default cond init
    void condInit();

public:
    Unit *getUMap(int x, int y);

    Army *getArmies(int n);

    int getCurrentTurn() const;

    bool getTeamActive(int team);

    void loadUnitMap1();

    //comprueba rango, reduce attP y hace daño
    bool dealDamage(Unit *att, Unit *def);

    //mueve y reduce movP. rango comprobado a priori en board (check que no se salga del mapa)
    bool move(int x1, int y1, int x2, int y2);

    //mueve sin comprobar ni reducir movP (check que no se salga del mapa)
    bool forceMove(int x1, int y1, int x2, int y2);

    //comprueba si algun army ha perdido y lo saca del juego en ese caso
    bool checkLoss(int team);

    void advanceTurn();

    //comprueba si solo queda un army/alliance y le otorga la victoria si procede
    int checkWin();

    string showUMap();

    bool addUnit(int x, int y, Types type, int team);
};

#endif //PROYECTO_UNITMAP_H
