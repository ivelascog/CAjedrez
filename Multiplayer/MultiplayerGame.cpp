//
// Created by fer on 27/06/17.
//

#include <iostream>
#include "MultiplayerGame.h"

void MultiplayerGame::hostGame1() {
    board = new MultiplayerBoard();
    board->loadMap1();
    hostInit();
}

void MultiplayerGame::joinGame1() {
    board = new MultiplayerBoard();
    board->loadMap1();
    clientInit();
}

MultiplayerGame::~MultiplayerGame() {
    delete (host);
    delete (client);
    delete (board);
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
    host->close();
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

void MultiplayerGame::runGame() {
    int winner;
    if (isHost) {
        winner = hostLoop();
    } else {
        winner = clientLoop();
    }
    cout << "WINNER IS ";
    if (board->getUnits()->isAllianceActive()) {
        cout << "ALLIANCE ";
    } else {
        cout << "TEAM ";
    }
    cout << to_string(winner) + ":" << endl;
    board->getUnits()->massRemoveComplete();
    cout << board->printMap(winner) << endl;
}

int MultiplayerGame::clientLoop() {
    turn = 0;
    int winner = -1;

    while (winner == -1) {
        advanceTurn();
        for (int t = 0; t < board->getUnits()->getTeams(); t++) {
            if (winner == -1 && board->getUnits()->getTeamActive(t)) {
                board->setCurrentPlayerTeam(t);
                if (t == myTeam) {
                    winner = board->clientTurn(t, client);
                } else {
                    winner = board->clientPassive(t, client);
                }
            }
        }
        if (winner == -1) {
            board->getUnits()->checkTurnLoss();
            winner = board->getUnits()->checkWin();
        }
    }

    return winner;
}

int MultiplayerGame::hostLoop() {
    turn = 0;
    int winner = -1;

    while (winner == -1) {
        advanceTurn();
        for (int t = 0; t < board->getUnits()->getTeams(); t++) {
            if (winner == -1 && board->getUnits()->getTeamActive(t)) {
                board->setCurrentPlayerTeam(t);
                if (t == myTeam) {
                    winner = board->hostTurn(t, host);
                } else {
                    winner = board->hostPassive(t, host);
                }
            }
        }
        if (winner == -1) {
            board->getUnits()->checkTurnLoss();
            winner = board->getUnits()->checkWin();
        }
    }

    return winner;
}

void MultiplayerGame::advanceTurn() {
    turn++;
    board->getUnits()->advanceTurn();
}
