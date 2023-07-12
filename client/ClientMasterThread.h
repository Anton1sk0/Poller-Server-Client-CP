#ifndef CLIENTMASTERTHREAD_H
#define CLIENTMASTERTHREAD_H

#include "ClientArgumentManager.h"
#include "ClientThread.h"
#include "ClientWorkerThread.h"
#include "ClientSocketManager.h"


class MasterThread : public Thread {
public:
    MasterThread(int portNum,string serverName, int numThreads, ArgumentManager * argumentManager);
    virtual ~MasterThread();
    
    void main();
private:
    ArgumentManager * argumentManager;
    int portNum;
    string serverName;
    WorkerThread** workerThreads;
    int numThreads;
};

#endif /* CLIENTMASTERTHREAD_H */

