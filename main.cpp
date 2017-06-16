#include <iostream>
#include <typeinfo>
#include "Board.h"

int main() {
    Terrain t = Plains();
    std::cout << t.terrainStats() << endl;
    return 0;
}