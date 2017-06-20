#include <iostream>
#include "Board.h"

int main() {
    Board b = Board();
    b.loadMap1();
    cout << b.printMap(1) << endl;
    Unit *u = b.getUnits()->getUMap(3, 0);
    b.walk(u, 3, 3);
    return 0;
}