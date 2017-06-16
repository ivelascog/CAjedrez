#include <iostream>
#include <typeinfo>
#include "Board.h"

int main() {
    UnitMap *uMap = new UnitMap();
    uMap->loadUnitMap1();
    std::cout << uMap->showUMap() << endl;
    uMap->getArmies(0)->killAll();
    std::cout << to_string(uMap->checkWin()) << endl;
    std::cout << uMap->showUMap() << endl;
    return 0;
}