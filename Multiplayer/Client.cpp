//
// Created by ivelascog on 26/06/17.
//

#include <iostream>
#include "Client.h"

bool Client::initializeClient(int team) {
    SocketHelper::write(this->mySocket, to_string(team));
    string msg = SocketHelper::read(this->mySocket);

    bool isConnected = (msg == "Connection Successful");

    while (!SocketHelper::isOver(msg)) {
        cout << msg << endl;
        msg = SocketHelper::read(mySocket);
    }

    return isConnected;
}

Client::Client(string hostIP) {
    this->mySocket = SocketHelper::startClient(SocketHelper::DEFAULT_PORT, hostIP);

    if (mySocket == -1) {
        throw runtime_error("Error: could not establish connection with host");
    }
}
