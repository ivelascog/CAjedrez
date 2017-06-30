
#include "Multiplayer/MultiplayerGame.h"

int main() {
    MultiplayerGame mg = MultiplayerGame();
    mg.hostGameCastleAssault();
    //mg.joinGameCastleAssault();
    mg.runGame();
}