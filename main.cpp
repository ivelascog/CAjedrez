
#include "Game.h"
#include "Multiplayer.h"

int main() {
    Multiplayer m = Multiplayer();
    m.startServer(4545);
    m.write("HOlA");
    return 0;
}