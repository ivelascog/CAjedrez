//
// Created by fer on 23/06/17.
//

#include <iostream>
#include "Menu.h"

using namespace std;

Multiplayer *Menu::showMenu() {
    cout << "1 - Play Local" << endl;
    cout << "2 - Host game" << endl;
    cout << "3 - Connect game" << endl;
    string aux;
    getline(cin, aux);
    int option = atoi(aux);
    switch (option) {
        case 1 :
            return NULL;

        case 2:
            Multiplayer *m = new Multiplayer();
            m->startServer(m->DEFAULT_PORT);
            return m;

        case 3:
            Multiplayer *mc = new Multiplayer();
            cout << "Please introduce host IP:" << endl;
            getline(cin, aux);
            mc->startClient(mc->DEFAULT_PORT, aux);
            return mc;

        default:
            break;
    }
}
