//
// Created by fer on 9/06/17.
//

#include "Soldier.h"

string Soldier::typeStats() {
    return "Soldier Unit:\nMov:" + to_string(movm) + "\tHealth" + to_string(health) + "\tDamage" + to_string(damage) +
           "\tRange" +
           to_string(range);
}
