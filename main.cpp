#include <iostream>
#include <typeinfo>
#include "Board.h"

int main() {
    UnitMap *uMap = new UnitMap();
    uMap->loadUnitMap1();
    std::cout << uMap->showUMap() << endl;
    std::cout << "0: " + to_string(uMap->checkLoss(0)) << endl;
    std::cout << "1: " + to_string(uMap->checkLoss(1)) << endl;
    std::cout << "Winner: " + to_string(uMap->checkWin()) << endl;
    std::cout << uMap->showUMap() << endl;
    std::cout << "0: " + to_string(uMap->checkLoss(0)) << endl;
    std::cout << "1: " + to_string(uMap->checkLoss(1)) << endl;
    std::cout << "Winner: " + to_string(uMap->checkWin()) << endl;
    std::cout << uMap->showUMap() << endl;
    std::cout << "0: " + to_string(uMap->checkLoss(0)) << endl;
    std::cout << "1: " + to_string(uMap->checkLoss(1)) << endl;
    std::cout << "Winner: " + to_string(uMap->checkWin()) << endl;
    std::cout << uMap->showUMap() << endl;
    uMap->forceMove(3, 9, 4, 6);
    std::cout << "0: " + to_string(uMap->checkLoss(0)) << endl;
    std::cout << "1: " + to_string(uMap->checkLoss(1)) << endl;
    std::cout << "Winner: " + to_string(uMap->checkWin()) << endl;
    std::cout << uMap->showUMap() << endl;
    return 0;
}