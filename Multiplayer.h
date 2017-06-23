//
// Created by ivelascog on 23/06/17.
//

#ifndef PROYECTO_MULTIPLAYER_H
#define PROYECTO_MULTIPLAYER_H

#include <string>

using namespace std;

class Multiplayer {
    char buffer[256];
    int clientSocket;
    bool isServer;
public:
    int startServer(int puerto);

    int startClient(int puerto, string ip);

    string read();

    int write(string msg);


};


#endif //PROYECTO_MULTIPLAYER_H
