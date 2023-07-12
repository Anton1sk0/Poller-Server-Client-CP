#ifndef CLIENTSOCKETMANAGER_H
#define CLIENTSOCKETMANAGER_H

#include <netinet/in.h>
#include <string>
using namespace std;

class SocketManager {
public:
    SocketManager(int port,string serverName);
    virtual ~SocketManager();
    
    void open();
    void close();
    int connect();
    bool isAvailable();
    int getSocket();
private:
    int port;
    int sock;
    string serverName;
    bool available = false;
    struct sockaddr_in server;
    struct sockaddr *serverptr = (struct sockaddr*)&server;
    struct hostent *rem;
};


#endif /* CLIENTSOCKETMANAGER_H */

