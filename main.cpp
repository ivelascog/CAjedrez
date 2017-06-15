#include <iostream>
#include <typeinfo>
#include "Board.h"

int main() {
    UnitMap um = UnitMap();
    um.loadUnitMap1();
    std::cout << um.getArmies(1)->fullReport() << endl;
    return 0;
}