//
// Created by fer on 13/06/17.
//

#ifndef PROYECTO_UNITMAP_H
#define PROYECTO_UNITMAP_H

#include "Units/Unit.h"
#include "Units/Army.h"
#include <array>

class UnitMap {
    vector<vector<Unit *>> uMap;
    vector<Army *> armies;
    vector<Army *> cemetery;
    vector<bool> teamActive;
    int height;
    int width;
    int teams;
    bool allianceActive = false;
    int currentTurn;
    string mapIdentifier = "";
    vector<string> teamNames;

    //losscons
    vector<bool> wipeIsLoss;
    vector<bool> unitIsEssential;
    vector<vector<Unit *>> essentials;
    vector<bool> lossAfterXTurns;
    vector<int> turnsToLose;
    vector<bool> defendPos;
    vector<vector<std::array<int, 2>>> posToDefend;

    //default cond init
    void condInit();

public:
    int getTeams() const;

    bool isAllianceActive() const;

    //Devuelve la ud que hay en la pos enviada como atributo.
    Unit *getUMap(int x, int y);

    //Devuelve el army enviada como atributo
    Army *getArmies(int n);

    //Devuelve el turno actual
    int getCurrentTurn() const;

    //Devuelve true si el team enviado está activo en ese momento.
    bool getTeamActive(int team);

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

    //Devuelve true si la u1 es hostil towards ud2.
    bool isHostile(Unit *u1, Unit *u2);

    //Devuelve la altura del mapa de uds.
    int getHeight() const;

    //Devuelve la anchura del mapa de uds.
    int getWidth() const;

    //Devuelve la alianza del team enviado como atributo.
    int getAlliance(int team);

    //Comprueba si ha perdido alguno de los teams.
    void checkLossAll();

    //Comprueba si se han llevado a cabo el número máximo de turnos permitidos, y en ese caso, se da
    //el juego por perdido.
    void checkTurnLoss();

    //Devuelve un string con el minireport de todas las armys.
    string completeMiniReport();

    //Te devuelve un report completo de la ud cuya id corresponde con la enviada como atributo.
    string consultUnitByID(int id);

    //Devueelve un string con el estado de la unidad defensora tras haber recibido el ataque.
    string placeboAttack(Unit *att, Unit *def);

    Unit *getUnitByID(int id);

    //Inicializa el mapa de uds.
    void loadUnitMap1();

    void initMap(int width, int height);

    void addEssential(Unit *u, int team);

    void addPosToDefend(int x, int y, int team);

    void wipeIsNotLoss(int t);

    void turnLimit(int turn, int team);

    void addToAlliance(int team, int alliance);

    bool isHostile(int team1, int team2);

    void loadUnitMapCastleAssault();

    int isPosToDefend(int x, int y, int team);

    vector<string> getTeamNames() const;

    string getMapIdentifier() const;
};

#endif //PROYECTO_UNITMAP_H
