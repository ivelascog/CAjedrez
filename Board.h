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
#define RESET 0

#include "UnitMap.h"
#include "TerrainMap.h"
#include <stack>

class Board {
private:
    int auxPos[2];
    UnitMap *units;
    TerrainMap *terrain;
    int width;
    int height;
public:
    Board();

    void loadMap1();

    UnitMap *getUnits() const;

    TerrainMap *getTerrain() const;

    string printMap(int team);

    vector<vector<int>> inRange(Unit *u);

    vector<vector<bool >> inRangeHostile(Unit *u);

    vector<vector<int>> accessible(Unit *u);

    vector<vector<bool>> isAccessible(Unit *u);

    stack<array<int, 2>> walk(Unit *u, int destX, int destY);
};


#endif //PROYECTO_BOARD_H
