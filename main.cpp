#include <iostream>
#include <typeinfo>
#include "Board.h"

int main() {
    TerrainMap tMap = TerrainMap();
    tMap.loadTerrainMap1();
    std::cout << tMap.showTMap() << endl;
    return 0;
}