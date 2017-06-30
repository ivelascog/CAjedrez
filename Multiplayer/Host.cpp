//
// Created by ivelascog on 26/06/17.
//

#include <iostream>
#include "Host.h"

Host::Host(int teams, int hostTeam) {
    clients = vector<int>((unsigned long) teams, -1);
    clients[hostTeam] = -2;
    team = hostTeam;
    int clientCount = 0;
    serverSocket = SocketHelper::startServer(SocketHelper::DEFAULT_PORT);

    bool aux = true;

    while (aux) {

        int sock = SocketHelper::receiveClient(serverSocket);
        string team = SocketHelper::read(sock);
        int rTeam = atoi(const_cast<char *> (team.c_str()));
        if (rTeam < teams && clients[rTeam] == -1) {
            clients[rTeam] = sock;
            SocketHelper::write(sock, "Connection successful");
            clientCount++;
            cout << to_string(clientCount) + " clients connected" << endl;
        } else {
            cout << "Connection failed: incorrect team sent by client" << endl;
            string s = "Team not valid; available teams are: ";
            for (int j = 0; j < teams; j++) {
                if (clients[j] == -1) {
                    s += to_string(j) + " ";
                }
            }
            SocketHelper::write(sock, s);
        }
        SocketHelper::sendOver(sock);

        aux = false;

        for (int i = 0; i < teams && !aux; i++) {
            if (clients[i] == -1) {
                aux = true;
            }
        }
    }
}

void Host::close() {
    SocketHelper::closeConnection(serverSocket);
}

string Host::read(int team) {
    if (clients[team] == -1 || team == this->team || team >= clients.size()) {
        throw runtime_error("Error: read from wrong team");
    }
    return SocketHelper::read(clients[team]);
}

void Host::write(string msg, int team) {
    if (clients[team] == -1 || team == this->team || team >= clients.size()) {
        throw runtime_error("Error: wrote on wrong team");
    }
    SocketHelper::write(clients[team], msg);
}

string Host::readAndBroadcast(int team) {
    if (clients[team] == -1 || team == this->team || team >= clients.size()) {
        throw runtime_error("Error: read from wrong team");
    }
    string msg = SocketHelper::read(clients[team]);

    for (int i = 0; i < clients.size(); i++) {
        if (clients[i] != -1 && clients[i] != -2 && i != team) {
            write(msg, i);
        }
    }
    return msg;
}

void Host::broadcast(string msg) {
    for (int i = 0; i < clients.size(); i++) {
        if (clients[i] != -1 && clients[i] != -2) {
            write(msg, i);
        }
    }
}

Host::~Host() {
    /*
    clients.clear();
     */
}

int Host::getTeam() const {
    return team;
}
