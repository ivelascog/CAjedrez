//
// Created by fer on 22/06/17.
//

#ifndef PROYECTO_GAME_H
#define PROYECTO_GAME_H

#include "Board.h"

class Game {
protected:
    Board *board;
    int turn;

public:
    //Aumenta el turno actual por 1.
    virtual void advanceTurn();

    //Funciçón encargada de la gestión integral del juego.
    void loadGame1();

    virtual ~Game();

    virtual void runGame();

    void loadGameCastleAssault();
};


#endif //PROYECTO_GAME_H
