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
    static const int DEFAULT_PORT = 15468;
    int startServer(int puerto);

    int startClient(int puerto, string ip);

    string read();

    int write(string msg);

    void closeConecction();


    string getIP();
};


#endif //PROYECTO_MULTIPLAYER_H
