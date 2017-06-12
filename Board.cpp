//
// Created by ivelascog on 8/06/17.
//

#include "Unit.h"
#include "Board.h"

void Board::addUnit(Unit u, int team) {
    armies[team].add(u);
}

void Board::populate(Population p) {


}

