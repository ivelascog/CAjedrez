//
// Created by fer on 22/06/17.
//

#ifndef PROYECTO_GAME_H
#define PROYECTO_GAME_H

#include "Board.h"

class Game {
    Board *board;
    int turn;

public:
    void advanceTurn();

    void runGame1();

    virtual ~Game();
};


#endif //PROYECTO_GAME_H
