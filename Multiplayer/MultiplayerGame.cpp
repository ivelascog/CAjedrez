//
// Created by fer on 27/06/17.
//

#include <iostream>
#include "MultiplayerGame.h"

void MultiplayerGame::hostGame1() {
    boardM = new MultiplayerBoard();
    boardM->loadMap1();
    hostInit();
}

void MultiplayerGame::joinGame1() {
    boardM = new MultiplayerBoard();
    boardM->loadMap1();
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
        cout << "Choose a team (0 to " + to_string(boardM->getUnits()->getTeams() - 1) + "):" << endl;
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
    host = new Host(boardM->getUnits()->getTeams(), myTeam);
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
        cout << "Choose a team to join the game (0 to " + to_string(boardM->getUnits()->getTeams() - 1) + "):" << endl;
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

void MultiplayerGame::runGame() {
    int winner;
    if (isHost) {
        winner = hostLoop();
    } else {
        winner = clientLoop();
    }
    cout << "WINNER IS ";
    if (boardM->getUnits()->isAllianceActive()) {
        cout << "ALLIANCE ";
    } else {
        cout << "TEAM ";
    }
    cout << to_string(winner) + ":" << endl;
    boardM->getUnits()->massRemoveComplete();
    cout << boardM->printMap(winner) << endl;
}

int MultiplayerGame::clientLoop() {
    turn = 0;
    int winner = -1;

    while (winner == -1) {
        advanceTurn();
        for (int t = 0; t < boardM->getUnits()->getTeams(); t++) {
            if (winner == -1 && boardM->getUnits()->getTeamActive(t)) {
                boardM->setCurrentPlayerTeam(t);
                if (t == myTeam) {
                    winner = boardM->clientTurn(t, client);
                } else {
                    winner = boardM->clientPassive(t, client);
                }
            }
        }
        if (winner == -1) {
            boardM->getUnits()->checkTurnLoss();
            winner = boardM->getUnits()->checkWin();
        }
    }

    return winner;
}

int MultiplayerGame::hostLoop() {
    turn = 0;
    int winner = -1;

    while (winner == -1) {
        advanceTurn();
        for (int t = 0; t < boardM->getUnits()->getTeams(); t++) {
            if (winner == -1 && boardM->getUnits()->getTeamActive(t)) {
                boardM->setCurrentPlayerTeam(t);
                if (t == myTeam) {
                    winner = boardM->hostTurn(t, host);
                } else {
                    winner = boardM->hostPassive(t, host);
                }
            }
        }
        if (winner == -1) {
            boardM->getUnits()->checkTurnLoss();
            winner = boardM->getUnits()->checkWin();
        }
    }

    return winner;
}