//
// Created by fer on 22/06/17.
//

#include <iostream>
#include "Game.h"

void Game::advanceTurn() {
    turn++;
    board->getUnits()->advanceTurn();
}

void Game::runGame1() {
    board = new Board();
    board->loadMap1();
    turn = 0;
    int winner = -1;

    while (winner == -1) {
        advanceTurn();
        for (int t = 0; t < board->getUnits()->getTeams(); t++) {
            if (winner == -1 && board->getUnits()->getTeamActive(t)) {
                winner = board->turn(t);
            }
        }
        if (winner == -1) {
            board->getUnits()->checkTurnLoss();
            winner = board->getUnits()->checkWin();
        }
    }

    cout << "WINNER IS TEAM " + to_string(winner) + ":" << endl;
    board->getUnits()->massRemoveComplete();
    cout << board->printMap(winner) << endl;
}

Game::~Game() {
    delete (board);
}
