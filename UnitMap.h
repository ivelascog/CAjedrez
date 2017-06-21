//
// Created by fer on 13/06/17.
//

#ifndef PROYECTO_UNITMAP_H
#define PROYECTO_UNITMAP_H

#include "Units/Unit.h"
#include "Units/Army.h"
#include <array>

class UnitMap {
    vector <vector<Unit *>> uMap;
    vector<Army *> armies;
    vector<Army *> cemetery;
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
public:
    bool isAllianceActive() const;

private:

    vector<bool> defendPos;
    vector <vector<std::array<int, 2>>> posToDefend;

    //default cond init
    void condInit();

public:
    Unit *getUMap(int x, int y);

    Army *getArmies(int n);

    int getCurrentTurn() const;

    bool getTeamActive(int team);

    void loadUnitMap1();

    //reduce attP y hace daño si corresponde
    bool dealDamage(Unit *att, Unit *def);

    //comprueba rango,
    bool attack(Unit *att, Unit *def);

    //mueve y reduce movP. rango comprobado a priori en board (check que no se salga del mapa)
    bool move(int x1, int y1, int x2, int y2);

    //mueve sin comprobar ni reducir movP (check que no se salga del mapa)
    bool forceMove(int x1, int y1, int x2, int y2);

    //comprueba si algun army ha perdido y lo saca del juego en ese caso
    bool checkLoss(int team);

    void advanceTurn();

    //comprueba si solo queda un army/alliance y le otorga la victoria si procede
    int checkWin();

    //muestra mapa por consola
    string showUMap();

    //añade ud al mapa y team correspondiente
    bool addUnit(int x, int y, Types type, int team);

    //pasa los muertos de team al correspondiente cementerio y los quita del mapa
    int massRemove(int team);

    //pasa los muertos al correspondiente cementerio y los quita del mapa
    int massRemoveComplete();

    //pasa unit al correspondiente cementerio y
    bool removeUnit(Unit *ut);

    virtual ~UnitMap();

    bool isHostile(Unit *u1, Unit *u2);

    int getHeight() const;

    int getWidth() const;

    int getAlliance(int team);
};

#endif //PROYECTO_UNITMAP_H
