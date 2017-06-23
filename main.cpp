
#include <iostream>
#include "Multiplayer.h"

int main() {
    Multiplayer m = Multiplayer();
    m.startClient(6666, "193.147.56.245");
    cout << m.read();
    cout << m.read();

    return 0;
}
