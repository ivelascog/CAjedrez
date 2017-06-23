
#include "Game.h"
#include "Multiplayer.h"

int main() {
    Multiplayer m = Multiplayer();
    m.startServer(15468);
    m.write("HOlA, Pues parece que rula la cosa");
    m.write("turuuuuulaaaaa");
    m.closeConecction();
    return 0;
}