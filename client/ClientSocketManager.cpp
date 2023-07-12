#include <stdio.h>
#include <sys/types.h>	     /* sockets */
#include <sys/socket.h>	     /* sockets */
#include <netinet/in.h>	     /* internet sockets */
#include <unistd.h>          /* read, write, close */
#include <netdb.h>	         /* gethostbyaddr */
#include <stdlib.h>	         /* exit */
#include <string.h>	         /* strlen */
#include <iostream>
#include "ClientSocketManager.h"
#include <cstring>
using namespace std;

SocketManager::SocketManager(int port, string serverName) : port(port),sock(-1),serverName(serverName) {
   
}

SocketManager::~SocketManager() {
    close();
}

void SocketManager::open() {
    available = true;
    
    //create socket
    sock=socket(AF_INET, SOCK_STREAM,0);
    if (sock<0){
        perror ( "socket cannot be created");
        exit(EXIT_FAILURE);
    }else{
        cout <<"socket created \n"<<endl;
    }
    ////////////////////
    /* Find server address */
    if ((rem = gethostbyname(serverName.c_str())) == NULL) {	
	   herror("get host by name ERROR"); exit(1);
    }
    server.sin_family = AF_INET;       /* Internet domain */
    memcpy(&server.sin_addr, rem->h_addr, rem->h_length);
    server.sin_port = htons(port);         /* Server port */
       
}



void SocketManager::close() {
    available = false;
     if (this->sock != -1) {
        ::close(sock);
        cout<<"socket has been closed"<<endl;
        this->sock = -1;
    }
}

int SocketManager::connect() {
    serverptr = (struct sockaddr*)&server;
    
    printf("Connecting to %s port %d\n", serverName.c_str(), port);
    
    if (::connect(sock, serverptr, sizeof(server)) < 0){
	   perror("connect");
            return -1;
    }
    
    printf("Connected to %s port %d\n", serverName.c_str(), port);
    
    return 0;
}

bool SocketManager::isAvailable() {
    return available;
}

int SocketManager::getSocket()  { 
    return sock; 
}

