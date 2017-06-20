#include <iostream>
#include "Board.h"

int main() {
    Board b = Board();
    b.loadMap1();
    cout << b.printMap(1) << endl;
    Unit *u = b.getUnits()->getUMap(5, 0);
    b.inRange(u);
    return 0;
}