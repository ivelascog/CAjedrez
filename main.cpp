#include <iostream>
#include "Soldier.h"

int main() {
    Soldier *napoopan = new Soldier(0, 0 , 1);
    std::cout << napoopan->report() << std::endl;
    std::cout << napoopan->typeStats() << std::endl;
    return 0;
}