#include <iostream>
#include <typeinfo>
#include "Soldier.h"
#include "Army.h"

int main() {
    Soldier *napoopan = new Soldier(0, 0, 1);
    std::cout << napoopan->report() << std::endl;
    Army grandeArmee = Army(1);
    grandeArmee.add(0, 0, king);
    grandeArmee.add(0, 0, soldier);
    grandeArmee.add(0, 0, horse);
    grandeArmee.add(0, 0, horse);
    std::cout << grandeArmee.fullReport() << std::endl;
    grandeArmee.remove(3);
    std::cout << grandeArmee.fullReport() << std::endl;
    grandeArmee.getUnitByID(1)->takeDamage(10000);
    grandeArmee.massRemove();
    std::cout << grandeArmee.fullReport() << std::endl;
    return 0;
}