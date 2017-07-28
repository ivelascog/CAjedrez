#include <iostream>
#include <cstring>
#include <sstream>
#include "Board.h"//
// Created by ivelascog on 8/06/17.
//

Board::Board() {
    units = new UnitMap();
    terrain = new TerrainMap();
}

void Board::loadMap1() {
    units->loadUnitMap1();
    terrain->loadTerrainMap1();
    height = units->getHeight();
    width = units->getWidth();
}

void Board::loadCastleAssault() {
    units->loadUnitMapCastleAssault();
    terrain->loadTerrainCastleAssault();
    height = units->getHeight();
    width = units->getWidth();
}

string Board::printMap(int team) {
    string s = "";

    s += "\t";

    for (int i = 0; i < width; i++) {
        if (i < 100) {
            s += " ";
        }
        s += to_string(i);
        if (i < 9) {
            s += " ";
        }
    }

    s += "\n";

    for (int i = 0; i < height; i++) {
        s += to_string(i) + "\t";
        for (int j = 0; j < width; j++) {
            s += "[";
            if (terrain->getTMap(j, i)->isObstacle()) {
                s += "\033[5;" + to_string(YELLOWBG) + "m \033[0m";
            } else if (units->getUMap(j, i) != nullptr) {
                s += "\033[";
                switch (units->isPosToDefend(j, i, team)) {
                    case 1:
                        s += to_string(CYANBG) + ";";
                        break;
                    case 2:
                        s += to_string(PINKBG) + ";";
                        break;
                    case 3:
                        s += to_string(BLUEBG) + ";";
                        break;
                    default:
                        break;
                }
                if (units->getUMap(j, i)->getTeam() == team) {
                    s += to_string(GREEN);
                } else if (units->isAllianceActive() &&
                           units->getAlliance(team) == units->getAlliance(units->getUMap(j, i)->getTeam())) {
                    s += to_string(BLUE);
                } else {
                    s += to_string(RED);
                }
                s += "m";
                s += units->getUMap(j, i)->getIcon();
                s += "\033[" + to_string(RESET) + "m";
            } else {
                switch (units->isPosToDefend(j, i, team)) {
                    case 1:
                        s += "\033[5;" + to_string(CYANBG) + "m \033[0m";
                        break;
                    case 2:
                        s += "\033[5;" + to_string(PINKBG) + "m \033[0m";
                        break;
                    case 3:
                        s += "\033[5;" + to_string(BLUEBG) + "m \033[0m";
                        break;
                    default:
                        s += " ";
                        break;
                }
            }
            s += "]";
        }
        s += "\n";
    }
    return s;
}


vector<vector<int>> Board::accessible(Unit *u) {
    return accessible(u, 0);
}

vector<vector<int>> Board::accessible(Unit *u, int moveExhaust) {
    int aux;

    vector<vector<int>> map = std::vector<std::vector<int>>
            ((unsigned long) width, vector<int>((unsigned long) height, 0));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (terrain->getTMap(j, i)->isObstacle() == 1) {
                map[j][i] = -1;
            } else if (units->getUMap(j, i) != nullptr) {
                map[j][i] = -2;
            }
        }
    }

    map[u->getPosX()][u->getPosY()] = u->getMovm() - moveExhaust + 1;

    for (int l = (u->getMovm() - moveExhaust + 1); l > 1; l--) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (map[j][i] == l) {
                    if (((j - 1) >= 0) && ((map[j - 1][i]) == 0)) {
                        if ((abs(terrain->getTMap(j - 1, i)->getHeight() -
                                 terrain->getTMap(j, i)->getHeight()) < 2) &&
                            terrain->getTMap(j - 1, i)->isHorizontal() &&
                            terrain->getTMap(j, i)->isHorizontal()) {
                            aux = ((l - 1) - terrain->getTMap(j - 1, i)->getPenMov());
                            map[j - 1][i] = max(aux, 1);
                        }
                    }
                    if (((j + 1) < width) && ((map[j + 1][i]) == 0)) {
                        if ((abs(terrain->getTMap(j + 1, i)->getHeight() -
                                 terrain->getTMap(j, i)->getHeight()) < 2) &&
                            terrain->getTMap(j + 1, i)->isHorizontal() &&
                            terrain->getTMap(j, i)->isHorizontal()) {
                            aux = ((l - 1) - terrain->getTMap(j + 1, i)->getPenMov());
                            map[j + 1][i] = max(aux, 1);
                        }
                    }
                    if (((i - 1) >= 0) && ((map[j][i - 1]) == 0)) {
                        if ((abs(terrain->getTMap(j, i - 1)->getHeight() -
                                 terrain->getTMap(j, i)->getHeight()) < 2) &&
                            terrain->getTMap(j, i - 1)->isVertical() &&
                            terrain->getTMap(j, i)->isVertical()) {
                            aux = ((l - 1) - terrain->getTMap(j, i - 1)->getPenMov());
                            map[j][i - 1] = max(aux, 1);
                        }
                    }
                    if (((i + 1) < height) && ((map[j][i + 1]) == 0)) {
                        if ((abs(terrain->getTMap(j, i + 1)->getHeight() -
                                 terrain->getTMap(j, i)->getHeight()) < 2) &&
                            terrain->getTMap(j, i + 1)->isVertical() &&
                            terrain->getTMap(j, i)->isVertical()) {
                            aux = ((l - 1) - terrain->getTMap(j, i + 1)->getPenMov());
                            map[j][i + 1] = max(aux, 1);
                        }
                    }
                }
            }
        }
    }

    return map;
}

vector<vector<int>> Board::inRange(Unit *u) {
    return rangeNoClip(u->getPosX(), u->getPosY(), u->getRange());
}

UnitMap *Board::getUnits() const {
    return units;
}

TerrainMap *Board::getTerrain() const {
    return terrain;
}

vector<vector<bool>> Board::inRangeHostile(Unit *u) {
    return rangeNoClipHostile(u->getPosX(), u->getPosY(), u->getRange(), u);
}

vector<vector<bool>> Board::isAccessible(Unit *u) {
    vector<vector<bool>> map = std::vector<std::vector<bool>>((unsigned long) width,
                                                              vector<bool>((unsigned long) height, false));
    vector<vector<int>> aux = accessible(u);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            map[j][i] = (aux[j][i] > 0);
        }
    }
    map[u->getPosX()][u->getPosY()] = false;
    return map;
}

stack<array<int, 2>> Board::walk(Unit *u, int destX, int destY) {
    if (!isAccessible(u)[destX][destY]) {
        throw runtime_error("Not accessible or out of range");
    }

    stack<array<int, 2>> walk;
    vector<vector<int>> map = accessible(u);
    walk.push({destX, destY});
    while (map[destX][destY] <= (u->getMovm())) {
        if (map[destX + 1][destY] > map[destX][destY]) {
            destX = destX + 1;
        } else if (map[destX - 1][destY] > map[destX][destY]) {
            destX = destX - 1;
        } else if (map[destX][destY + 1] > map[destX][destY]) {
            destY = destY + 1;
        } else if (map[destX][destY - 1] > map[destX][destY]) {
            destY = destY - 1;
        }
        walk.push({destX, destY});
    }
    return walk;
}

string Board::printUnitActions(Unit *u) {
    return printUnitActions(u, u->getTeam());
}

vector<vector<int>> Board::accessibleAttacks(Unit *u) {
    return accessibleAttacks(u, 0);
}

vector<vector<int>> Board::accessibleAttacks(Unit *u, int moveExhaust) {
    vector<vector<int>> map = accessible(u, moveExhaust);
    vector<vector<int>> auxMap;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[j][i] > 0 &&
                ((j + 1 < width && map[j + 1][i] <= 0) || (j - 1 >= 0 && map[j - 1][i] <= 0) ||
                 (i + 1 < height && map[j][i + 1] <= 0) || (i - 1 >= 0 && map[j][i - 1] <= 0))) {
                auxMap = rangeNoClip(j, i, u->getRange());
                for (int a = 0; a < height; a++) {
                    for (int b = 0; b < width; b++) {
                        if (auxMap[b][a] > 0 && map[b][a] <= 0) {
                            map[b][a] = -3;
                        }
                    }
                }
            }
        }
    }
    return map;
}


vector<vector<int>> Board::rangeNoClip(int x, int y, int range) {
    int ux = x;
    int uy = y;
    vector<vector<int>> map = std::vector<std::vector<int>>((unsigned long) width, vector<int>((unsigned long) height));
    map[ux][uy] = 1;

    if (range == 0) {
        return map;
    }

    range = range + 1;

    for (int l = 1; l < range; l++) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (map[j][i] == l) {
                    if (((j - 1) >= 0) && ((map[j - 1][i]) == 0)) {
                        map[j - 1][i] = (l + 1);
                    }
                    if (((j + 1) < width) && ((map[j + 1][i]) == 0)) {
                        map[j + 1][i] = (l + 1);
                    }
                    if (((i - 1) >= 0) && ((map[j][i - 1]) == 0)) {
                        map[j][i - 1] = (l + 1);
                    }
                    if (((i + 1) < height) && ((map[j][i + 1]) == 0)) {
                        map[j][i + 1] = (l + 1);
                    }
                }
            }
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[j][i] == (range - 1)) {
                if (((j - 1) >= 0) && ((map[j - 1][i]) == 0)) {
                    map[j - 1][i] = range;
                }
                if (((j + 1) < width) && ((map[j + 1][i]) == 0)) {
                    map[j + 1][i] = range;
                }
                if (((i - 1) >= 0) && ((map[j][i - 1]) == 0)) {
                    map[j][i - 1] = range;
                }
                if (((i + 1) < height) && ((map[j][i + 1]) == 0)) {
                    map[j][i + 1] = range;
                }
                if (((j - 1) >= 0) && ((i - 1) >= 0) && ((map[j - 1][i - 1]) == 0)) {
                    map[j - 1][i - 1] = range;
                }
                if (((j - 1) >= 0) && ((i + 1) < height) && ((map[j - 1][i + 1]) == 0)) {
                    map[j - 1][i + 1] = range;
                }
                if (((j + 1) < width) && ((i - 1) >= 0) && ((map[j + 1][i - 1]) == 0)) {
                    map[j + 1][i - 1] = range;
                }
                if (((j + 1) < width) && ((i + 1) < height) && ((map[j + 1][i + 1]) == 0)) {
                    map[j + 1][i + 1] = range;
                }
            }
        }
    }

    if (range >= 6) {
        int n = range;
        int t = (range - 6) / 2;
        for (int q = 0; q <= t; q++) {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if (map[j][i] == (n)) {
                        if (((j - 1) >= 0) && ((map[j - 1][i]) == 0)) {
                            if (ux - (j - 1) < range) {
                                map[j - 1][i] = n + 1;
                            }
                        }
                        if (((j + 1) < width) && ((map[j + 1][i]) == 0)) {
                            if ((j + 1) - ux < range) {
                                map[j + 1][i] = n + 1;
                            }
                        }
                        if (((i - 1) >= 0) && ((map[j][i - 1]) == 0)) {
                            if (uy - (i - 1) < range) {
                                map[j][i - 1] = n + 1;
                            }
                        }
                        if (((i + 1) < height) && ((map[j][i + 1]) == 0)) {
                            if ((i + 1) - uy < range) {
                                map[j][i + 1] = n + 1;
                            }
                        }
                    }
                }
            }
            n++;
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (terrain->getTMap(j, i)->isObstacle()) {
                map[j][i] = -1;
            }
        }
    }

    return map;
}

vector<vector<bool>> Board::rangeNoClipHostile(int x, int y, int range, Unit *u) {
    vector<vector<bool>> map = std::vector<std::vector<bool>>((unsigned long) width,
                                                              vector<bool>((unsigned long) height, false));
    vector<vector<int>> aux = rangeNoClip(x, y, range);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (aux[j][i] > 0 && units->getUMap(j, i) != nullptr) {
                map[j][i] = units->isHostile(u, units->getUMap(j, i));
            }
        }
    }
    return map;
}

int Board::turn(int t) {
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
        int aux = atoi(const_cast<char *>(input.c_str()));

        int aux2 = 0;

        if (aux == 5) {
            units->getArmies(t)->actionsToZero();
        } else if (aux == 2) {
            consultVisibleUnits(t);
        } else {
            cout << "Select any unit by ID: " << endl;
            getline(cin, input);
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

                        switch (atoi(const_cast<char *>(input.c_str()))) {
                            case 1:
                                if (u->getMoveP() <= 0) {
                                    cout << "No such action available." << endl;
                                } else {
                                    cout << "Select destination (\"x, y\"):" << endl;
                                    int x;
                                    int y;
                                    getline(cin, input);
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

bool Board::targetsExist(Unit *u) {
    auto map = inRangeHostile(u);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[j][i]) {
                return true;
            }
        }
    }
    return false;
}

void Board::consultVisibleUnits(int team) {
    int aux = 0;
    string input;
    while (aux != -1) {
        cout << units->completeMiniReport() << endl;
        cout << "Select any unit by ID (or -1 to return): " << endl;

        getline(cin, input);
        aux = atoi(const_cast<char *>(input.c_str()));

        if (aux != -1) {
            cout << units->consultUnitByID(aux) << endl;
            if (units->getUnitByID(aux)->getTeam() != currentPlayerTeam) {
                units->getUnitByID(aux)->resetAP();
            }
            cout << printUnitActions(units->getUnitByID(aux)) << endl;

            if (units->getUnitByID(aux)->getTeam() != currentPlayerTeam) {
                units->getUnitByID(aux)->setMoveP(0);
                units->getUnitByID(aux)->setAttP(0);
            }

            cout << "Press enter to continue..." << endl;
            getline(cin, input);

        }
    }
}

string Board::walkAndPrint(Unit *u, int destX, int destY) {
    stack<array<int, 2>> path = walk(u, destX, destY);
    string s = "";

    while (!path.empty()) {
        s += to_string(path.top()[0]) + ", " + to_string(path.top()[1]);
        path.pop();
        if (!path.empty()) {
            s += " / ";
        }
    }

    s += "\n";

    return s;
}


Board::~Board() {
    delete (units);
    delete (terrain);
}

int Board::getCurrentPlayerTeam() const {
    return currentPlayerTeam;
}

void Board::setCurrentPlayerTeam(int currentPlayerTeam) {
    Board::currentPlayerTeam = currentPlayerTeam;
}

string Board::printUnitActions(Unit *u, int team) {
    if (u->getTeam() == team) {
        return printUnitActionsAlly(u, team);
    } else if (units->isAllianceActive() && units->getAlliance(team) ==
                                            units->getAlliance(u->getTeam())) {
        return printUnitActionsAlly(u, team);
    } else {
        return printUnitActionsEnemy(u, team);
    }
}

string Board::printUnitActionsAlly(Unit *u, int team) {

    vector<vector<int>> acc = std::vector<std::vector<int>>
            ((unsigned long) width, vector<int>((unsigned long) height, 0));
    if (u->getMoveP() > 0 && u->getAttP() > 0) {
        acc = accessibleAttacks(u);
    } else if (u->getMoveP() > 0) {
        acc = accessible(u);
    } else if (u->getAttP() > 0) {
        acc = inRange(u);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (acc[j][i] > 0) {
                    acc[j][i] = -3;
                }
            }
        }
    }
    string s = "";

    s += "\t";

    for (int i = 0; i < width; i++) {
        if (i < 100) {
            s += " ";
        }
        s += to_string(i);
        if (i < 9) {
            s += " ";
        }
    }

    s += "\n";

    for (int i = 0; i < height; i++) {
        s += to_string(i) + "\t";
        for (int j = 0; j < width; j++) {
            s += "[";
            if (terrain->getTMap(j, i)->isObstacle()) {
                s += "\033[" + to_string(YELLOWBG) + "m \033[0m";
            } else if (acc[j][i] == -3 && units->getUMap(j, i) == nullptr) {
                s += "\033[" + to_string(REDBG) + "m \033[0m";
            } else if (units->getUMap(j, i) != nullptr) {
                s += "\033[";
                switch (units->isPosToDefend(j, i, team)) {
                    case 1:
                        s += to_string(CYANBG) + ";";
                        break;
                    case 2:
                        s += to_string(PINKBG) + ";";
                        break;
                    case 3:
                        s += to_string(BLUEBG) + ";";
                        break;
                    default:
                        break;
                }
                if (units->getUMap(j, i)->getTeam() == team) {
                    s += to_string(GREEN);
                } else if (units->isAllianceActive() &&
                           units->getAlliance(team) == units->getAlliance(units->getUMap(j, i)->getTeam())) {
                    s += to_string(BLUE);
                } else {
                    if (acc[j][i] == -3) {
                        s += "1;";
                        s += to_string(REDBG);
                        s += ";";
                        s += to_string(BLACK);
                    } else {
                        s += to_string(RED);
                    }
                }
                s += "m";
                s += units->getUMap(j, i)->getIcon();
                s += "\033[" + to_string(RESET) + "m";
            } else if (acc[j][i] > 0) {
                s += "\033[" + to_string(GREENBG) + "m \033[0m";
            } else {
                switch (units->isPosToDefend(j, i, team)) {
                    case 1:
                        s += "\033[5;" + to_string(CYANBG) + "m \033[0m";
                        break;
                    case 2:
                        s += "\033[5;" + to_string(PINKBG) + "m \033[0m";
                        break;
                    case 3:
                        s += "\033[5;" + to_string(BLUEBG) + "m \033[0m";
                        break;
                    default:
                        s += " ";
                        break;
                }
            }
            s += "]";
        }
        s += "\n";
    }
    return s;
}

string Board::printUnitActionsEnemy(Unit *u, int team) {

    vector<vector<int>> acc = std::vector<std::vector<int>>
            ((unsigned long) width, vector<int>((unsigned long) height, 0));
    if (u->getMoveP() > 0 && u->getAttP() > 0) {
        acc = accessibleAttacks(u);
    } else if (u->getMoveP() > 0) {
        acc = accessible(u);
    } else if (u->getAttP() > 0) {
        acc = inRange(u);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (acc[j][i] > 0) {
                    acc[j][i] = -3;
                }
            }
        }
    }
    string s = "";

    s += "\t";

    for (int i = 0; i < width; i++) {
        if (i < 100) {
            s += " ";
        }
        s += to_string(i);
        if (i < 9) {
            s += " ";
        }
    }

    s += "\n";

    for (int i = 0; i < height; i++) {
        s += to_string(i) + "\t";
        for (int j = 0; j < width; j++) {
            s += "[";
            if (terrain->getTMap(j, i)->isObstacle()) {
                s += "\033[" + to_string(YELLOWBG) + "m \033[0m";
            } else if (acc[j][i] == -3 && units->getUMap(j, i) == nullptr) {
                s += "\033[" + to_string(REDBG) + "m \033[0m";
            } else if (units->getUMap(j, i) != nullptr) {
                s += "\033[";
                switch (units->isPosToDefend(j, i, team)) {
                    case 1:
                        s += to_string(CYANBG) + ";";
                        break;
                    case 2:
                        s += to_string(PINKBG) + ";";
                        break;
                    case 3:
                        s += to_string(BLUEBG) + ";";
                        break;
                    default:
                        break;
                }
                if (units->isHostile(u->getTeam(), units->getUMap(j, i)->getTeam())) {
                    if (acc[j][i] == -3) {
                        s += "1;";
                        s += to_string(REDBG);
                        s += ";";
                    }
                    if (units->getUMap(j, i)->getTeam() == team) {
                        s += to_string(GREEN);
                    } else if (units->isAllianceActive() &&
                               units->getAlliance(team) == units->getAlliance(units->getUMap(j, i)->getTeam())) {
                        s += to_string(BLUE);
                    } else {
                        s += to_string(BLACK);
                    }
                } else {
                    s += to_string(RED);
                }
                s += "m";
                s += units->getUMap(j, i)->getIcon();
                s += "\033[" + to_string(RESET) + "m";
            } else if (acc[j][i] > 0) {
                s += "\033[" + to_string(GREENBG) + "m \033[0m";
            } else {
                switch (units->isPosToDefend(j, i, team)) {
                    case 1:
                        s += "\033[5;" + to_string(CYANBG) + "m \033[0m";
                        break;
                    case 2:
                        s += "\033[5;" + to_string(PINKBG) + "m \033[0m";
                        break;
                    case 3:
                        s += "\033[5;" + to_string(BLUEBG) + "m \033[0m";
                        break;
                    default:
                        s += " ";
                        break;
                }
            }
            s += "]";
        }
        s += "\n";
    }
    return s;
}
