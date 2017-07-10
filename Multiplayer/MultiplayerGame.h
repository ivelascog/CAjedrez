//
// Created by fer on 27/06/17.
//

#ifndef PROYECTO_MULTIPLAYERGAME_H
#define PROYECTO_MULTIPLAYERGAME_H

#include "Client.h"
#include "Host.h"
#include "../Game.h"
#include "MultiplayerBoard.h"

class MultiplayerGame : public Game {
protected:
    int myTeam;
    bool isHost = false;
    Host *host;
    Client *client;
    MultiplayerBoard *board;
public:

    void hostGame1();

    virtual ~MultiplayerGame();

    virtual void hostInit();

    void joinGame1();

    virtual void clientInit();

    void runGame();

    int hostLoop();

    int clientLoop();

    void advanceTurn();

    void hostGameCastleAssault();

    void joinGameCastleAssault();

    virtual MultiPlayerBoard *getBoard();
};


#endif //PROYECTO_MULTIPLAYERGAME_H
