//
// Created by alserrano on 9/06/17.
//

#include "King.h"

string King::typeStats() {
    return "King Unit:\nMov:" + to_string(movm) + "\tHealth" + to_string(health) + "\tDamage" + to_string(damage) +
           "\tRange" +
           to_string(range);
}
