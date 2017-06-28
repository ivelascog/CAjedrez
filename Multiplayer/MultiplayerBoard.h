//
// Created by fer on 27/06/17.
//

#ifndef PROYECTO_MULTIPLAYERBOARD_H
#define PROYECTO_MULTIPLAYERBOARD_H

#include "../Board.h"
#include "Host.h"
#include "Client.h"

class MultiplayerBoard : public Board {
public:
    int hostTurn(int t, Host *host);

    int clientTurn(int t, Client *client);

    int hostPassive(int t, Host *host);

    int clientPassive(int t, Client *client);
};


#endif //PROYECTO_MULTIPLAYERBOARD_H