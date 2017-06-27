//
// Created by ivelascog on 23/06/17.
//

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <ifaddrs.h>
#include "SocketHelper.h"

static void error(const char *msg) {
    perror(msg);
}

int SocketHelper::startServer(int puerto) {
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = puerto;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons((uint16_t) portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) {
        error("ERROR on binding");
        closeConnection(sockfd);
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (bind(sockfd, (struct sockaddr *) &serv_addr,
                 sizeof(serv_addr)) < 0) {
            error("ERROR on binding (unsuccessful socket reset)");
        }
    }
    listen(sockfd, 5);
    return sockfd;
}

int SocketHelper::startClient(int puerto, std::string ip) {
    int sockfd, portno;
    struct sockaddr_in serv_addr;
    struct in_addr ipStruct;
    struct hostent *server;

    portno = puerto;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    inet_aton(ip.c_str(), &ipStruct);
    server = gethostbyaddr(&ipStruct, sizeof(ipStruct), AF_INET);

    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
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
        return -1;

    }

    return sockfd;
}

string SocketHelper::read(int sock) {
    string msg = "";
    char buff[4];
    bzero(&buff, 4);

    recv(sock, &buff, sizeof(int), 0);

    int length = int((unsigned char) (buff[0]) |
                     (unsigned char) (buff[1]) << 8 |
                     (unsigned char) (buff[2]) << 16 |
                     (unsigned char) (buff[3]) << 24);

    char buff2[length + 1];
    bzero(&buff2, length + 1);

    recv(sock, &buff2, length, 0);

    msg = buff2;
    return msg;

}

int SocketHelper::write(int sock, string msg) {
    const char *buff = msg.c_str();

    int size = (int) msg.size();
    const char *bytes = (const char *) &size;
    send(sock, bytes, sizeof(size), 0);
    int result = (int) send(sock, buff, msg.size(), 0);
    return result;
}

void SocketHelper::closeConnection(int sock) {
    shutdown(sock, 2);
    close(sock);
}

string SocketHelper::getIP() {
    struct ifaddrs *ifAddrStruct = NULL;
    struct ifaddrs *ifa = NULL;
    void *tmpAddrPtr = NULL;

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) { // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr = &((struct sockaddr_in *) ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            string ip = addressBuffer;
            if (ip != "127.0.0.1") {
                return ip;
            }
        }
    }
    return nullptr;
}

int SocketHelper::receiveClient(int serverSocket) {
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    newsockfd = accept(serverSocket,
                       (struct sockaddr *) &cli_addr,
                       &clilen);
    if (newsockfd < 0)
        error("ERROR on accept");
    return newsockfd;
}

bool SocketHelper::isOver(string msg) {
    return msg.find(ENDMSG) != std::string::npos;
}

void SocketHelper::sendOver(int sock) {
    write(sock, ENDMSG);
}

SocketHelper::SocketHelper() {
}


