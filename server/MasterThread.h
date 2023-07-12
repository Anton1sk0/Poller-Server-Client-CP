#ifndef MASTERTHREAD_H
#define MASTERTHREAD_H

#include "ArgumentManager.h"
#include "ProducerConsumerQueue.h"
#include "Thread.h"
#include "WorkerThread.h"
#include "SocketManager.h"


class MasterThread : public Thread {
public:
    MasterThread(ArgumentManager * argumentManager, ProducerConsumerQueue * queue, WorkerThread ** workerThreads);
    virtual ~MasterThread();
    
    void main();
    void exit();
private:
    ArgumentManager * argumentManager;
    ProducerConsumerQueue * queue;
    WorkerThread ** workerThreads;
    SocketManager socketManager;
};

#endif /* MASTERTHREAD_H */

