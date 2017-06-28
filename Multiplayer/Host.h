//
// Created by ivelascog on 26/06/17.
//

#ifndef PROYECTO_HOST_H
#define PROYECTO_HOST_H

#include <vector>
#include "SocketHelper.h"

using namespace std;

class Host {
    int team;
    int serverSocket;
    vector<int> clients;
public:
    Host(int teams, int hostTeam);

    void close();

    string read(int team);

    void write(string msg, int team);

    string readAndBroadcast(int team);

    void broadcast(string msg);
};


#endif //PROYECTO_HOST_H
