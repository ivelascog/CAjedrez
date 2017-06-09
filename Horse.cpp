//
// Created by fer on 9/06/17.
//

#include "Horse.h"

string Horse::typeStats() {
    return "Horse Unit:\nMov:"+to_string(movm)+"\tHealth"+to_string(health)+"\tDamage"+to_string(damage)+"\tRange"+
           to_string(range);
}
