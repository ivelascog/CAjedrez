//
// Created by fer on 27/06/17.
//

#include <iostream>
#include "MultiplayerGame.h"

void MultiplayerGame::hostGame1() {
    board = new Board();
    board->loadMap1();
    hostInit();
}

void MultiplayerGame::joinGame1() {
    board = new Board();
    board->loadMap1();
    clientInit();
}

MultiplayerGame::~MultiplayerGame() {
    delete (host);
    delete (client);
}

void MultiplayerGame::hostInit() {
    isHost = true;
    bool loop = true;

    while (loop) {
        cout << "Choose a team (0 to " + to_string(board->getUnits()->getTeams() - 1) + "):" << endl;
        string aux;
        getline(cin, aux);
        try {
            myTeam = stoi(aux);
            loop = false;
        } catch (exception &e) {
            cout << "Error: not a valid number" << endl;
        }
    }
    cout << "Your IP is: " + SocketHelper::getIP() << endl;
    host = new Host(board->getUnits()->getTeams(), myTeam);
}

void MultiplayerGame::clientInit() {
    isHost = false;
    bool loop = true;

    string aux;
    while (loop) {
        cout << "Introduce host IP:" << endl;
        getline(cin, aux);
        try {
            client = new Client(aux);
            loop = false;
        } catch (exception &e) {
            cout << "Error: couldn't connect to specified IP" << endl;
        }
    }

    loop = true;
    while (loop) {
        cout << "Choose a team to join the game (0 to " + to_string(board->getUnits()->getTeams() - 1) + "):" << endl;
        string aux2;
        getline(cin, aux2);
        try {
            myTeam = stoi(aux2);
            loop = !client->initializeClient(myTeam);
            if (loop) {
                delete (client);
                client = new Client(aux);
            }
        } catch (exception &e) {
            cout << "Error: not a valid number" << endl;
        }
    }
    cout << "Connection established" << endl;
}
