#include <iostream>
#include <typeinfo>
#include "Soldier.h"
#include "Army.h"

int main() {
    Soldier *napoopan = new Soldier(0, 0 , 1);
    std::cout << napoopan->report() << std::endl;
    Army grandeArmee = Army(1);
    grandeArmee.add(0,0,king);
    return 0;
}