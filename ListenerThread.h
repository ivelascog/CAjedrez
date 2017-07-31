#ifndef LISTENERTHREAD_H
#define LISTENERTHREAD_H
#include <QThread>
#include "Multiplayer/Client.h"
#include "Multiplayer/Host.h"

class ListenerThread : public QThread
{
    Q_OBJECT
public:
    ListenerThread(Host* host, int client);
    ListenerThread(Client* client);
signals:
    void move(int x, int y);
    void attack(int x, int y);
    void select(int x, int y);
    void endTurn();
private:
    Host* host;
    Client* client;
    void run();
    bool running = true;
    int teamListened;
};

#endif // LISTENERTHREAD_H
