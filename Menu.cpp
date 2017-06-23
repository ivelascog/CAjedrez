//
// Created by fer on 23/06/17.
//

#include <iostream>
#include <arpa/inet.h>
#include "Menu.h"

using namespace std;

Multiplayer *Menu::showMenu() {
    cout << "1 - Play Local" << endl;
    cout << "2 - Host game" << endl;
    cout << "3 - Connect game" << endl;
    string aux;
    getline(cin, aux);
    Multiplayer *m = new Multiplayer();
    int option = atoi(const_cast<char *>(aux.c_str()));
    switch (option) {
        case 1 :
            return NULL;

        case 2:
            m->startServer(m->DEFAULT_PORT);
            return m;

        case 3:
            cout << "Please introduce host IP:" << endl;
            getline(cin, aux);
            m->startClient(m->DEFAULT_PORT, aux);
            return m;

        default:
            break;
    }
}
