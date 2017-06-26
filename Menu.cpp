//
// Created by fer on 23/06/17.
//

#include <iostream>
#include <arpa/inet.h>
#include "Menu.h"

using namespace std;

SocketHelper *Menu::showMenu() {
    cout << "1 - Play Local" << endl;
    cout << "2 - Host game" << endl;
    cout << "3 - Connect game" << endl;
    string aux;
    getline(cin, aux);
    int option = atoi(const_cast<char *>(aux.c_str()));
    switch (option) {
        case 1 :
            return NULL;

        case 2:
            cout << "waiting for connections" << endl;
            cout << "Your IP is " + SocketHelper::getIP() << endl;
            flush(cout);
            SocketHelper::startServer(SocketHelper::DEFAULT_PORT);
            cout << "Conection complete ";

        case 3:
            cout << "Please introduce host IP:" << endl;
            getline(cin, aux);
            SocketHelper::startClient(SocketHelper::DEFAULT_PORT, aux);

        default:
            break;
    }
}
