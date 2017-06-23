//
// Created by ivelascog on 23/06/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>
#include "multiplayer.h"


void error(const char *msg) {
    perror(msg);
    exit(1);
}

int multiplayer::startServer(int puerto) {
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    isServer = true;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = puerto;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons((uint16_t) portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd,
                       (struct sockaddr *) &cli_addr,
                       &clilen);
    if (newsockfd < 0)
        error("ERROR on accept");
    bzero(buffer, 256);
    this->clientSocket = newsockfd;
    return 0;
}

int multiplayer::startClient(int puerto, std::string ip) {
    int sockfd, portno;
    struct sockaddr_in serv_addr;
    struct in_addr ipStruct;
    struct hostent *server;

    portno = puerto;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    inet_aton("192.0.2.34", &ipStruct);
    server = gethostbyaddr(&ipStruct, sizeof(ipStruct), AF_INET);

    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        this->clientSocket = -1;
        return -1;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr,
          (char *) &serv_addr.sin_addr.s_addr,
          (size_t) server->h_length);
    serv_addr.sin_port = htons((uint16_t) portno);

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR connecting");
        this->clientSocket = -1;
        return -1;

    }

    bzero(buffer, 256);
    this->clientSocket = sockfd;
    return 0;
}

string multiplayer::read() {
    string msg = "";
    char buff[1024];

    int leidos = (int) recv(clientSocket, &buff, 1024, 0);

    msg = buff;
    return msg;

}

int multiplayer::write(string msg) {
    const char *buff = msg.c_str();
    return (int) send(clientSocket, buff, msg.size(), 0);
}
