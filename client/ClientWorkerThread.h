#ifndef CLIENTWORKERTHREAD_H
#define CLIENTWORKERTHREAD_H

#include <string>

#include "ClientArgumentManager.h"
#include "ClientSocketManager.h"
#include "ClientThread.h"
#include "Transport.h"

using namespace std;

class WorkerThread : public Thread {
public:
    WorkerThread(SocketManager *socketManager, string line);
    virtual ~WorkerThread();
    
    void main();
private:
    SocketManager *socketManager;
    string line;
    Transport transport;
    
    void process(int fd);
    
    string getNameFromLine(string line);
    string getVoteFromLine(string line);
};


#endif /* CLIENTWORKERTHREAD_H */

