#include <iostream>
#include "Board.h"

int main() {
    Board b = Board();
    b.loadMap1();
    cout << b.printMap(1) << endl;
    return 0;
}