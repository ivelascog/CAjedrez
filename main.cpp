
#include "Game.h"
#include "Multiplayer.h"

int main() {
    Multiplayer multiplayer = Multiplayer();
    multiplayer.startServer(multiplayer.DEFAULT_PORT);
    multiplayer.getIP(0);
    return 0;
}