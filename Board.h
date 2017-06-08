//
// Created by ivelascog on 8/06/17.
//

#ifndef PROYECTO_BOARD_H
#define PROYECTO_BOARD_H

#include <vector>
#include "GenericUnit.h"

class Board {
private:
    GenericUnit table[11][11];
    int tableInt[11][11];
    std::vector<GenericUnit> peones;
    std::vector<GenericUnit> horseman;
    std::vector<GenericUnit> archers;
    GenericUnit king;
public:
    void init();

    void isValid();
};


#endif //PROYECTO_BOARD_H
