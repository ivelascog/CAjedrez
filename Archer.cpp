//
// Created by fer on 8/06/17.
//

#include "Archer.h"

string Archer::typeStats() {
    return "Archer Unit:\nMov:"+to_string(movm)+"\tHealth"+to_string(health)+"\tDamage"+to_string(damage)+"\tRange"+
            to_string(range);
}
