#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include "SocketManager.h"

using namespace std;

SocketManager::SocketManager(int port) : port(port), sock(-1) {
}

SocketManager::~SocketManager() {
    close();
}

void SocketManager::open() {
    available = true;

    //create listening socket 
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket cannot be created");
        exit(EXIT_FAILURE);
    } else {
        cout << "socket created" << endl;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET; /* Internet domain */
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port); /* The given port */

    //bind

    if (bind(sock, (struct sockaddr *) &server, sizeof (server)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    } else {
        cout << "socket binded" << endl;
    }

    //listen 
    if (listen(sock, 500) < 0) { ////second argument double check************************************************************
        perror("listen failed");
        exit(EXIT_FAILURE);
    } else {
        cout << "socket listen on " << port << endl;
    }
}

void SocketManager::close() {
    available = false;
    if (this->sock != -1) {
        shutdown(this->sock, SHUT_RDWR);
        ::close(sock);
        this->sock = -1;
    }
}

int SocketManager::accept() {
    struct sockaddr_in client;
    socklen_t clientlen = sizeof (client);
    int newsock;
    if ((newsock = ::accept(sock, (struct sockaddr *) &client, &clientlen)) < 0) {
        if (available) {
            perror("accept");
            exit(EXIT_FAILURE);
        } 
    } else {
        std::cout << "Accepted connection" << std::endl;
    }
    return newsock;
}

bool SocketManager::isAvailable() {
    return available;
}
