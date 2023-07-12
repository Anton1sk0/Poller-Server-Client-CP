
#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include "ArgumentManager.h"
#include "ProducerConsumerQueue.h"
#include "PartyManager.h"
#include "VoteManager.h"
#include "Thread.h"
#include "Transport.h"


class WorkerThread : public Thread {
public:
    WorkerThread(ArgumentManager * argumentManager, ProducerConsumerQueue * queue, PartyManager * partyManager, VoteManager * voteManager);
    virtual ~WorkerThread();
    
    void main();
private:
    ArgumentManager * argumentManager;
    ProducerConsumerQueue * queue;
    PartyManager * partyManager;
    VoteManager * voteManager;  
    
    Transport transport;
    
    void process(int fd);
};

#endif /* WORKERTHREAD_H */

