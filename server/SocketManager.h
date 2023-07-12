
#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

class SocketManager {
public:
    SocketManager(int port);
    virtual ~SocketManager();
    
    void open();
    void close();
    int accept();
    
    bool isAvailable();
private:
    int port;
    int sock;
    bool available = false;
};

#endif /* SOCKETMANAGER_H */

