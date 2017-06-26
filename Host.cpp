//
// Created by ivelascog on 26/06/17.
//

#include "Host.h"

Host::Host(int teams, int hostTeam) {
    clients = vector<int>((unsigned long) teams, -1);
    clients[hostTeam] = -2;
    team = hostTeam;
    serverSocket = SocketHelper::startServer(SocketHelper::DEFAULT_PORT);

    bool aux = true;

    while (aux) {

        int sock = SocketHelper::receiveClient(serverSocket);
        string team = SocketHelper::read(sock);
        int rTeam = atoi(const_cast<char *> (team.c_str()));
        if (rTeam < teams && clients[rTeam] == -1) {
            clients[rTeam] = sock;
            SocketHelper::write(sock, "Connection successful");
        } else {
            SocketHelper::write(sock, "Team not valid; available teams are ");
            for (int j = 0; j < teams; j++) {
                if (clients[j] == -1) {
                    SocketHelper::write(sock, to_string(j) + " ");
                }
            }
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
