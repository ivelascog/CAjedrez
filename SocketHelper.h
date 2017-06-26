//
// Created by ivelascog on 23/06/17.
//

#ifndef PROYECTO_MULTIPLAYER_H
#define PROYECTO_MULTIPLAYER_H
#define ENDMSG "/>"

#include <string>

using namespace std;

class SocketHelper {
    static int mySocket;
public:

    string endMsg = ENDMSG;

    static const int DEFAULT_PORT = 15468;

    static int startServer(int puerto);

    static int startClient(int puerto, string ip);

    static int receiveClient(int serverSocket);

    static string read(int sock);

    static int write(int sock, string msg);

    static void closeConnection(int sock);

    static string getIP();

    static bool isOver(string msg);

    static void sendOver(int sock);

private:
    SocketHelper();
};


#endif //PROYECTO_MULTIPLAYER_H
