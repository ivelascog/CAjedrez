//
// Created by fer on 27/06/17.
//

#include <iostream>
#include <sstream>
#include "MultiplayerBoard.h"

int MultiplayerBoard::hostTurn(int t, Host *host) {

    string input;

    if (t < 0 || t >= units->getTeams()) {
        throw runtime_error("No such team");
    }

    cout << "-------------------" << endl;
    cout << "||TURN " + to_string(units->getCurrentTurn()) + " / TEAM " + to_string(t) + "||" << endl;
    cout << "-------------------" << endl;
    units->getArmies(t)->actionReset();


    while (units->getArmies(t)->getAvailableActions() > 0 && units->checkWin() == -1) {
        cout << printMap(t) << endl;
        cout << units->getArmies(t)->fullReport() << endl;
        cout << "Remaining actions this turn: " + to_string(units->getArmies(t)->getAvailableActions()) << endl;

        cout << "1 - Play" << endl;
        cout << "2 - Consult units" << endl;
        cout << "5 - Skip" << endl;
        getline(cin, input);
        host->broadcast(input);

        int aux = atoi(const_cast<char *>(input.c_str()));

        int aux2 = 0;

        if (aux == 5) {
            units->getArmies(t)->actionsToZero();
        } else if (aux == 2) {
            consultVisibleUnits(t);
        } else {
            cout << "Select any unit by ID: " << endl;
            getline(cin, input);
            host->broadcast(input);
            Unit *u = units->getArmies(t)->getUnitByID(atoi(const_cast<char *>(input.c_str())));
            if (u != nullptr) {
                if (u->getAttP() <= 0 && u->getMoveP() <= 0) {
                    cout << "No available action points for selected unit." << endl;
                } else {
                    bool virgin = true;
                    aux = 0;
                    while ((u->getAttP() > 0 || u->getMoveP() > 0) && aux != 3 && aux != 4 && units->checkWin() == -1) {
                        aux2 = 0;
                        cout << printUnitActions(u) << endl;
                        cout << u->report() << endl;
                        cout << u->typeStats() << endl;
                        cout << "Choose an action:" << endl;
                        if (u->getMoveP() > 0) {
                            cout << "1 - Move" << endl;
                        }
                        if (u->getAttP() > 0) {
                            cout << "2 - Attack" << endl;
                        }
                        cout << "3 - End actions with selected unit" << endl;
                        if (virgin) {
                            cout << "4 - Undo selection" << endl;
                        }
                        getline(cin, input);
                        host->broadcast(input);

                        switch (atoi(const_cast<char *>(input.c_str()))) {
                            case 1:
                                if (u->getMoveP() <= 0) {
                                    cout << "No such action available." << endl;
                                } else {
                                    cout << "Select destination (\"x, y\"):" << endl;
                                    int x;
                                    int y;
                                    getline(cin, input);
                                    host->broadcast(input);
                                    stringstream ss(input);
                                    string tok;
                                    getline(ss, tok, ',');
                                    x = atoi(const_cast<char *>(tok.c_str()));
                                    getline(ss, tok, ',');
                                    y = atoi(const_cast<char *>(tok.c_str()));
                                    if (x < width && x >= 0 && y < height && y >= 0) {
                                        if (accessible(u)[x][y] > 0) {
                                            cout << "Path: " + walkAndPrint(u, x, y) << endl;
                                            cout << "1 - Confirm" << endl;
                                            cout << "2 - Cancel" << endl;
                                            getline(cin, input);
                                            host->broadcast(input);
                                            aux2 = atoi(const_cast<char *>(input.c_str()));
                                            if (aux2 == 1 || aux2 == 0/*= enter*/) {
                                                units->move(u->getPosX(), u->getPosY(), x, y);
                                                virgin = false;
                                            }
                                        } else {
                                            cout << "Destination is not valid." << endl;
                                        }
                                    } else {
                                        cout << "Destination not in bounds." << endl;
                                    }
                                }
                                break;

                            case 2:
                                if (u->getAttP() <= 0) {
                                    cout << "No such action available." << endl;
                                } else {
                                    if (targetsExist(u)) {
                                        cout << "Select target (\"x, y\"):" << endl;
                                        int x;
                                        int y;
                                        getline(cin, input);
                                        host->broadcast(input);
                                        stringstream ss(input);
                                        string tok;
                                        getline(ss, tok, ',');
                                        x = atoi(const_cast<char *>(tok.c_str()));
                                        getline(ss, tok, ',');
                                        y = atoi(const_cast<char *>(tok.c_str()));
                                        if (x < width && x >= 0 && y < height && y >= 0) {
                                            if (inRangeHostile(u)[x][y]) {
                                                cout << units->placeboAttack(u, units->getUMap(x, y)) << endl;
                                                cout << "1 - Confirm" << endl;
                                                cout << "2 - Cancel" << endl;
                                                getline(cin, input);
                                                host->broadcast(input);
                                                aux2 = atoi(const_cast<char *>(input.c_str()));
                                                if (aux2 == 1 || aux2 == 0/*= enter*/) {
                                                    units->attack(u, units->getUMap(x, y));
                                                    virgin = false;
                                                    units->massRemoveComplete();
                                                }
                                            } else {
                                                cout << "Target is not valid." << endl;
                                            }

                                        } else {
                                            cout << "Target not in bounds." << endl;
                                        }
                                    } else {
                                        cout << "No targets available." << endl;
                                    }
                                }
                                break;

                            case 3:
                                aux = 3;
                                break;

                            case 4:
                                if (virgin) {
                                    aux = 4;
                                } else {
                                    cout << "No such action available." << endl;
                                }
                                break;

                            default:
                                cout << "No such action available." << endl;
                                break;
                        }
                    }
                    if (aux != 4 && (aux2 == 1 || aux2 == 0)) {
                        u->setMoveP(0);
                        u->setAttP(0);
                        units->getArmies(t)->reduceActions();
                    }
                    units->massRemoveComplete();
                }
            } else {
                cout << "No such unit exists." << endl << endl;
            }
        }
    }

    return units->checkWin();
}

int MultiplayerBoard::hostPassive(int t, Host *host) {
    bool printM = true;
    bool printU;

    string input;
    string auxStorage;
    if (t < 0 || t >= units->getTeams()) {
        throw runtime_error("No such team");
    }

    cout << "-------------------" << endl;
    cout << "||TURN " + to_string(units->getCurrentTurn()) + " / TEAM " + to_string(t) + "||" << endl;
    cout << "-------------------" << endl;
    units->getArmies(t)->actionReset();


    while (units->getArmies(t)->getAvailableActions() > 0 && units->checkWin() == -1) {
        if (printM) {
            cout << "\n\nWaiting for player " + to_string(currentPlayerTeam) + "..." << endl;
            cout << printMap(host->getTeam()) << endl;
            cout << "Remaining actions this turn: " + to_string(units->getArmies(t)->getAvailableActions()) << endl;
            printM = false;
        }
        printU = true;

        input = host->readAndBroadcast(t);
        int aux = atoi(const_cast<char *>(input.c_str()));

        int aux2 = 0;

        if (aux == 5) {
            units->getArmies(t)->actionsToZero();
        } else if (aux == 2) {
            //should not show consult units!
        } else {
            input = host->readAndBroadcast(t);
            Unit *u = units->getArmies(t)->getUnitByID(atoi(const_cast<char *>(input.c_str())));
            if (u != nullptr) {
                if (u->getAttP() <= 0 && u->getMoveP() <= 0) {
                } else {
                    bool virgin = true;
                    aux = 0;
                    while ((u->getAttP() > 0 || u->getMoveP() > 0) && aux != 3 && aux != 4 && units->checkWin() == -1) {
                        aux2 = 0;
                        if (printU) {
                            cout << "\n\nWaiting for player " + to_string(currentPlayerTeam) + "..." << endl;
                            string s = printUnitActions(u, host->getTeam());
                            cout << s << endl;
                            cout << u->report() << endl;
                            cout << u->typeStats() << endl;
                            printU = false;
                        }
                        input = host->readAndBroadcast(t);

                        switch (atoi(const_cast<char *>(input.c_str()))) {
                            case 1:
                                if (u->getMoveP() <= 0) {
                                } else {
                                    int x;
                                    int y;
                                    input = host->readAndBroadcast(t);
                                    stringstream ss(input);
                                    string tok;
                                    getline(ss, tok, ',');
                                    x = atoi(const_cast<char *>(tok.c_str()));
                                    getline(ss, tok, ',');
                                    y = atoi(const_cast<char *>(tok.c_str()));
                                    if (x < width && x >= 0 && y < height && y >= 0) {
                                        if (accessible(u)[x][y] > 0) {
                                            auxStorage = "Path: " + walkAndPrint(u, x, y);
                                            input = host->readAndBroadcast(t);
                                            aux2 = atoi(const_cast<char *>(input.c_str()));
                                            if (aux2 == 1 || aux2 == 0/*= enter*/) {
                                                cout << auxStorage << endl;
                                                printU = true;
                                                units->move(u->getPosX(), u->getPosY(), x, y);
                                                virgin = false;
                                            }
                                        }
                                    }
                                }
                                break;

                            case 2:
                                if (u->getAttP() <= 0) {
                                } else {
                                    if (targetsExist(u)) {
                                        int x;
                                        int y;
                                        input = host->readAndBroadcast(t);
                                        stringstream ss(input);
                                        string tok;
                                        getline(ss, tok, ',');
                                        x = atoi(const_cast<char *>(tok.c_str()));
                                        getline(ss, tok, ',');
                                        y = atoi(const_cast<char *>(tok.c_str()));
                                        if (x < width && x >= 0 && y < height && y >= 0) {
                                            if (inRangeHostile(u)[x][y]) {
                                                auxStorage = units->placeboAttack(u, units->getUMap(x, y));
                                                input = host->readAndBroadcast(t);
                                                aux2 = atoi(const_cast<char *>(input.c_str()));
                                                if (aux2 == 1 || aux2 == 0/*= enter*/) {
                                                    cout << auxStorage << endl;
                                                    printU = true;
                                                    units->attack(u, units->getUMap(x, y));
                                                    virgin = false;
                                                    units->massRemoveComplete();
                                                }
                                            }
                                        }
                                    }
                                }
                                break;

                            case 3:
                                aux = 3;
                                break;

                            case 4:
                                if (virgin) {
                                    aux = 4;
                                }
                                break;

                            default:
                                break;
                        }
                    }
                    if (aux != 4 && (aux2 == 1 || aux2 == 0)) {
                        printM = true;
                        u->setMoveP(0);
                        u->setAttP(0);
                        units->getArmies(t)->reduceActions();
                    }
                    units->massRemoveComplete();
                }
            }
        }
    }

    return units->checkWin();
}

int MultiplayerBoard::clientTurn(int t, Client *client) {

    string input;

    if (t < 0 || t >= units->getTeams()) {
        throw runtime_error("No such team");
    }

    cout << "-------------------" << endl;
    cout << "||TURN " + to_string(units->getCurrentTurn()) + " / TEAM " + to_string(t) + "||" << endl;
    cout << "-------------------" << endl;
    units->getArmies(t)->actionReset();


    while (units->getArmies(t)->getAvailableActions() > 0 && units->checkWin() == -1) {
        cout << printMap(t) << endl;
        cout << units->getArmies(t)->fullReport() << endl;
        cout << "Remaining actions this turn: " + to_string(units->getArmies(t)->getAvailableActions()) << endl;

        cout << "1 - Play" << endl;
        cout << "2 - Consult units" << endl;
        cout << "5 - Skip" << endl;
        getline(cin, input);
        client->write(input);
        int aux = atoi(const_cast<char *>(input.c_str()));

        int aux2 = 0;

        if (aux == 5) {
            units->getArmies(t)->actionsToZero();
        } else if (aux == 2) {
            consultVisibleUnits(t);
        } else {
            cout << "Select any unit by ID: " << endl;
            getline(cin, input);
            client->write(input);
            Unit *u = units->getArmies(t)->getUnitByID(atoi(const_cast<char *>(input.c_str())));
            if (u != nullptr) {
                if (u->getAttP() <= 0 && u->getMoveP() <= 0) {
                    cout << "No available action points for selected unit." << endl;
                } else {
                    bool virgin = true;
                    aux = 0;
                    while ((u->getAttP() > 0 || u->getMoveP() > 0) && aux != 3 && aux != 4 && units->checkWin() == -1) {
                        aux2 = 0;
                        cout << printUnitActions(u) << endl;
                        cout << u->report() << endl;
                        cout << u->typeStats() << endl;
                        cout << "Choose an action:" << endl;
                        if (u->getMoveP() > 0) {
                            cout << "1 - Move" << endl;
                        }
                        if (u->getAttP() > 0) {
                            cout << "2 - Attack" << endl;
                        }
                        cout << "3 - End actions with selected unit" << endl;
                        if (virgin) {
                            cout << "4 - Undo selection" << endl;
                        }
                        getline(cin, input);
                        client->write(input);

                        switch (atoi(const_cast<char *>(input.c_str()))) {
                            case 1:
                                if (u->getMoveP() <= 0) {
                                    cout << "No such action available." << endl;
                                } else {
                                    cout << "Select destination (\"x, y\"):" << endl;
                                    int x;
                                    int y;
                                    getline(cin, input);
                                    client->write(input);
                                    stringstream ss(input);
                                    string tok;
                                    getline(ss, tok, ',');
                                    x = atoi(const_cast<char *>(tok.c_str()));
                                    getline(ss, tok, ',');
                                    y = atoi(const_cast<char *>(tok.c_str()));
                                    if (x < width && x >= 0 && y < height && y >= 0) {
                                        if (accessible(u)[x][y] > 0) {
                                            cout << "Path: " + walkAndPrint(u, x, y) << endl;
                                            cout << "1 - Confirm" << endl;
                                            cout << "2 - Cancel" << endl;
                                            getline(cin, input);
                                            client->write(input);
                                            aux2 = atoi(const_cast<char *>(input.c_str()));
                                            if (aux2 == 1 || aux2 == 0/*= enter*/) {
                                                units->move(u->getPosX(), u->getPosY(), x, y);
                                                virgin = false;
                                            }
                                        } else {
                                            cout << "Destination is not valid." << endl;
                                        }
                                    } else {
                                        cout << "Destination not in bounds." << endl;
                                    }
                                }
                                break;

                            case 2:
                                if (u->getAttP() <= 0) {
                                    cout << "No such action available." << endl;
                                } else {
                                    if (targetsExist(u)) {
                                        cout << "Select target (\"x, y\"):" << endl;
                                        int x;
                                        int y;
                                        getline(cin, input);
                                        client->write(input);
                                        stringstream ss(input);
                                        string tok;
                                        getline(ss, tok, ',');
                                        x = atoi(const_cast<char *>(tok.c_str()));
                                        getline(ss, tok, ',');
                                        y = atoi(const_cast<char *>(tok.c_str()));
                                        if (x < width && x >= 0 && y < height && y >= 0) {
                                            if (inRangeHostile(u)[x][y]) {
                                                cout << units->placeboAttack(u, units->getUMap(x, y)) << endl;
                                                cout << "1 - Confirm" << endl;
                                                cout << "2 - Cancel" << endl;
                                                getline(cin, input);
                                                client->write(input);
                                                aux2 = atoi(const_cast<char *>(input.c_str()));
                                                if (aux2 == 1 || aux2 == 0/*= enter*/) {
                                                    units->attack(u, units->getUMap(x, y));
                                                    virgin = false;
                                                    units->massRemoveComplete();
                                                }
                                            } else {
                                                cout << "Target is not valid." << endl;
                                            }

                                        } else {
                                            cout << "Target not in bounds." << endl;
                                        }
                                    } else {
                                        cout << "No targets available." << endl;
                                    }
                                }
                                break;

                            case 3:
                                aux = 3;
                                break;

                            case 4:
                                if (virgin) {
                                    aux = 4;
                                } else {
                                    cout << "No such action available." << endl;
                                }
                                break;

                            default:
                                cout << "No such action available." << endl;
                                break;
                        }
                    }
                    if (aux != 4 && (aux2 == 1 || aux2 == 0)) {
                        u->setMoveP(0);
                        u->setAttP(0);
                        units->getArmies(t)->reduceActions();
                    }
                    units->massRemoveComplete();
                }
            } else {
                cout << "No such unit exists." << endl << endl;
            }
        }
    }

    return units->checkWin();
}

int MultiplayerBoard::clientPassive(int t, Client *client) {
    bool printM = true;
    bool printU;

    string input;
    string auxStorage;
    if (t < 0 || t >= units->getTeams()) {
        throw runtime_error("No such team");
    }

    cout << "-------------------" << endl;
    cout << "||TURN " + to_string(units->getCurrentTurn()) + " / TEAM " + to_string(t) + "||" << endl;
    cout << "-------------------" << endl;
    units->getArmies(t)->actionReset();


    while (units->getArmies(t)->getAvailableActions() > 0 && units->checkWin() == -1) {
        if (printM) {
            cout << "\n\nWaiting for player " + to_string(currentPlayerTeam) + "..." << endl;
            cout << printMap(client->getTeam()) << endl;
            cout << "Remaining actions this turn: " + to_string(units->getArmies(t)->getAvailableActions()) << endl;
            printM = false;
        }
        printU = true;

        input = client->read();
        int aux = atoi(const_cast<char *>(input.c_str()));

        int aux2 = 0;

        if (aux == 5) {
            units->getArmies(t)->actionsToZero();
        } else if (aux == 2) {
            //should not show consult units!
        } else {
            input = client->read();
            Unit *u = units->getArmies(t)->getUnitByID(atoi(const_cast<char *>(input.c_str())));
            if (u != nullptr) {
                if (u->getAttP() <= 0 && u->getMoveP() <= 0) {
                } else {
                    bool virgin = true;
                    aux = 0;
                    while ((u->getAttP() > 0 || u->getMoveP() > 0) && aux != 3 && aux != 4 && units->checkWin() == -1) {
                        aux2 = 0;
                        if (printU) {
                            cout << "\n\nWaiting for player " + to_string(currentPlayerTeam) + "..." << endl;
                            cout << printUnitActions(u, client->getTeam()) << endl;
                            cout << u->report() << endl;
                            cout << u->typeStats() << endl;
                            printU = false;
                        }
                        input = client->read();

                        switch (atoi(const_cast<char *>(input.c_str()))) {
                            case 1:
                                if (u->getMoveP() <= 0) {
                                } else {
                                    int x;
                                    int y;
                                    input = client->read();
                                    stringstream ss(input);
                                    string tok;
                                    getline(ss, tok, ',');
                                    x = atoi(const_cast<char *>(tok.c_str()));
                                    getline(ss, tok, ',');
                                    y = atoi(const_cast<char *>(tok.c_str()));
                                    if (x < width && x >= 0 && y < height && y >= 0) {
                                        if (accessible(u)[x][y] > 0) {
                                            auxStorage = "Path: " + walkAndPrint(u, x, y);
                                            input = client->read();
                                            aux2 = atoi(const_cast<char *>(input.c_str()));
                                            if (aux2 == 1 || aux2 == 0/*= enter*/) {
                                                cout << auxStorage << endl;
                                                printU = true;
                                                units->move(u->getPosX(), u->getPosY(), x, y);
                                                virgin = false;
                                            }
                                        }
                                    }
                                }
                                break;

                            case 2:
                                if (u->getAttP() <= 0) {
                                } else {
                                    if (targetsExist(u)) {
                                        int x;
                                        int y;
                                        input = client->read();
                                        stringstream ss(input);
                                        string tok;
                                        getline(ss, tok, ',');
                                        x = atoi(const_cast<char *>(tok.c_str()));
                                        getline(ss, tok, ',');
                                        y = atoi(const_cast<char *>(tok.c_str()));
                                        if (x < width && x >= 0 && y < height && y >= 0) {
                                            if (inRangeHostile(u)[x][y]) {
                                                auxStorage = units->placeboAttack(u, units->getUMap(x, y));
                                                input = client->read();
                                                aux2 = atoi(const_cast<char *>(input.c_str()));
                                                if (aux2 == 1 || aux2 == 0/*= enter*/) {
                                                    cout << auxStorage << endl;
                                                    printU = true;
                                                    units->attack(u, units->getUMap(x, y));
                                                    virgin = false;
                                                    units->massRemoveComplete();
                                                }
                                            }
                                        }
                                    }
                                }
                                break;

                            case 3:
                                aux = 3;
                                break;

                            case 4:
                                if (virgin) {
                                    aux = 4;
                                }
                                break;

                            default:
                                break;
                        }
                    }
                    if (aux != 4 && (aux2 == 1 || aux2 == 0)) {
                        printM = true;
                        u->setMoveP(0);
                        u->setAttP(0);
                        units->getArmies(t)->reduceActions();
                    }
                    units->massRemoveComplete();
                }
            }
        }
    }

    return units->checkWin();
}