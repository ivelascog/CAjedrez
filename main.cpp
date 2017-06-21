#include <iostream>
#include "Board.h"

int main() {
    Board b = Board();
    b.loadMap1();
    string s = "";
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 15; j++) {
            s += "[";
            if (b.getTerrain()->getTMap(j, i)->isObstacle()) {
                s += "o";
            } else {
                s += " ";
            }
            s += "]";
        }
        s += "\n";
    }
    cout << s << endl;
    cout << b.printMap(1) << endl;
    /*
    Unit *u = b.getUnits()->getUMap(3, 1);
    cout << b.printUnitActions(u) << endl;
    b.getUnits()->forceMove(u->getPosX(), u->getPosY(), 3, 3);
    cout << b.printUnitActions(u) << endl;*/
    return 0;
}