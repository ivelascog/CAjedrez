//
// Created by ivelascog on 8/06/17.
//

#ifndef PROYECTO_BOARD_H
#define PROYECTO_BOARD_H

#define REDBG 41
#define GREENBG 42
#define YELLOWBG 43
#define RED 31
#define BLUE 34
#define GREEN 32
#define BLACK 30
#define RESET 0

#include "UnitMap.h"
#include "TerrainMap.h"
#include <stack>

class Board {
private:
    UnitMap *units;
    TerrainMap *terrain;
    int width;
    int height;
public:
    Board();

    //report, seleccionar y ver info
    void consultVisibleUnits(int team);

    //carga nivel 1
    void loadMap1();

    virtual ~Board();

    //devuelve unitmap
    UnitMap *getUnits() const;

    //devuelve terrainmap
    TerrainMap *getTerrain() const;

    //string con el estado del mapa, unidades enemigas en rojo, aliadas en azul y propias en verde
    string printMap(int team);

    //devuelve un mapa de enteros con las casillas en rango de u
    vector<vector<int>> inRange(Unit *u);

    //devuelve un mapa de bool con las casillas hostiles en rango de u
    vector<vector<bool >> inRangeHostile(Unit *u);

    //devuelve un mapa de enteros con las casillas accesibles en el próximo movimiento de u
    vector<vector<int>> accessible(Unit *u);

    //devuelve un mapa de enteros con las casillas accesibles en el próximo movimiento de u + casillas amenazadas
    vector<vector<int>> accessibleAttacks(Unit *u);

    //devuelve un mapa de booleanos con las casillas accesibles por u
    vector<vector<bool>> isAccessible(Unit *u);

    //devuelve el camino a recorrer por u para moverse de su posición a una accesible
    stack<array<int, 2>> walk(Unit *u, int destX, int destY);

    //muestra el mapa de acciones posibles para u (bg verde para movimientos posibles y roja para enemigos en rango).
    string printUnitActions(Unit *u);

    //devuelve un mapa con casillas correspondientes a rango range en x, y
    vector<vector<int>> rangeNoClip(int x, int y, int range);

    //devuelve mapa con casillas hostiles a u en x, y para rango range
    vector<vector<bool>> rangeNoClipHostile(int x, int y, int range, Unit *u);

    //Función que gestiona el turno.
    int turn(int team);

    //Devuelve true si la ud tiene algún target en rango.
    bool targetsExist(Unit *u);

    //Devuelve un string con el camino seguido por la ud al moverse.
    string walkAndPrint(Unit *u, int destX, int destY);
};


#endif //PROYECTO_BOARD_H
