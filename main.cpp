
#include <iostream>
#include "Client.h"
#include "Host.h"

int main() {
    cout << "Your IP is: " + SocketHelper::getIP() << endl;
    Host host = Host(3, 0);
    host.close();

}