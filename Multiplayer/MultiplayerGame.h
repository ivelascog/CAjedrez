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
    int myTeam;
    bool isHost = false;
    Host *host;
    Client *client;
    MultiplayerBoard *boardM;
public:

    void hostGame1();

    virtual ~MultiplayerGame();

    void hostInit();

    void joinGame1();

    void clientInit();

    void runGame();

    int hostLoop();

    int clientLoop();
};


#endif //PROYECTO_MULTIPLAYERGAME_H