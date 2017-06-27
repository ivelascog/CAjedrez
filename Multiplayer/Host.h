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
};


#endif //PROYECTO_HOST_H
