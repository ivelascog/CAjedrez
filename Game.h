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
    //Aumenta el turno actual por 1.
    void advanceTurn();

    //Funciçón encargada de la gestión integral del juego.
    void runGame1();

    virtual ~Game();
};


#endif //PROYECTO_GAME_H
