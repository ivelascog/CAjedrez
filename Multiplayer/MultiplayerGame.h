//
// Created by fer on 27/06/17.
//

#ifndef PROYECTO_MULTIPLAYERBOARD_H
#define PROYECTO_MULTIPLAYERBOARD_H

#include "Client.h"
#include "Host.h"
#include "../Game.h"

class MultiplayerGame : public Game {
    int myTeam;
    bool isHost = false;
    Host *host;
    Client *client;
public:

    void hostGame1();

    virtual ~MultiplayerGame();

    void hostInit();

    void joinGame1();

    void clientInit();
};


#endif //PROYECTO_MULTIPLAYERBOARD_H
