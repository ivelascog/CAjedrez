//
// Created by ivelascog on 26/06/17.
//

#ifndef PROYECTO_CLIENT_H
#define PROYECTO_CLIENT_H

#include "SocketHelper.h"


class Client {
    int mySocket;
    int team;
public:
    bool initializeClient(int team);

    Client(string hostIP);

    string read();

    void write(string msg);
};


#endif //PROYECTO_CLIENT_H
