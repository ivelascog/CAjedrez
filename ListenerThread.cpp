#include "ListenerThread.h"

ListenerThread::ListenerThread(Host* host, int client)
{
    this->host = host;
    teamListened = client;
}

ListenerThread::ListenerThread(Client* client)
{
    this->client = client;
}

void ListenerThread::run()
{
    string msg;
    if (host != nullptr) {
        while (running) {
            msg = host->readAndBroadcast(teamListened);
            int x, y;
            switch (stoi(msg)) {
                case Move:
                    x = stoi(host->readAndBroadcast(teamListened));
                    y = stoi(host->readAndBroadcast(teamListened));
                    emit move(x, y);
                    break;
                case Attack:
                    x = stoi(host->readAndBroadcast(teamListened));
                    y = stoi(host->readAndBroadcast(teamListened));
                    emit attack(x, y);
                    break;
                case Select:
                    x = stoi(host->readAndBroadcast(teamListened));
                    y = stoi(host->readAndBroadcast(teamListened));
                    emit select(x, y);
                    break;
            }
        }
    } else {
        while (running) {
            msg = client->read();
            int x, y;
            switch (stoi(msg)) {
                case Move:
                    x = stoi(client->read());
                    y = stoi(client->read());
                    emit move(x, y);
                    break;
                case Attack:
                    x = stoi(client->read());
                    y = stoi(client->read());
                    emit attack(x, y);
                    break;
                case Select:
                    x = stoi(client->read());
                    y = stoi(client->read());
                    emit select(x, y);
                    break;
            }
        }
    }
}
