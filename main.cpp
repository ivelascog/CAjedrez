
#include <iostream>
#include "Client.h"

int main() {
    string ip;
    cout << "Introduza dirrecion IP del server" << endl;
    getline(cin, ip);
    cout << "Elige un team" << endl;
    string team;
    getline(cin, team);
    Client client = Client(ip);
    client.initializeClient(atoi(const_cast<char *>(team.c_str())));


}