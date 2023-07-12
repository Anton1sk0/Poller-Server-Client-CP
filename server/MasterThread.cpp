#include <iostream>
#include <fstream>

#include "MasterThread.h"
#include "SocketManager.h"

using namespace std;

void * startRoutineForWorkerThread(void * arg) {
    WorkerThread * thread = (WorkerThread*)arg;
    thread->main();
    return NULL;
}

MasterThread::MasterThread(ArgumentManager * argumentManager, ProducerConsumerQueue * queue, WorkerThread ** workerThreads) 
    : argumentManager(argumentManager), queue(queue), workerThreads(workerThreads), socketManager(argumentManager->port_num) {
    cout << "Master thread created " << endl;
}

MasterThread::~MasterThread() {
    cout << "Master thread destroyed " << endl;
}

void MasterThread::exit() {
    socketManager.close();
}
void MasterThread::main() {
    cout << "Master thread started" << endl;

    for (int i = 0; i < argumentManager->numWorkerThreads; i++) {
        cout << "Master thread: Creating worker thread " << i << endl; 
        
        pthread_create(&workerThreads[i]->tid, NULL, startRoutineForWorkerThread, workerThreads[i]);
    }
    ////////////////// open socket
    socketManager.open();
    
     ///limit for active connections? ******************************************************************
    while (socketManager.isAvailable()) {
        // accept ....
        
        int newsock= socketManager.accept();
      
        // produce
        queue->place(newsock);
    }
    
    
    socketManager.close();
    cout << "Master thread: Waiting for threads to exit \n";
    
    for (int i = 0; i < argumentManager->numWorkerThreads; i++) {
        queue->place(-1);
    }
    
    for (int i = 0; i < argumentManager->numWorkerThreads; i++) {
        pthread_join(workerThreads[i]->tid, NULL);
    }
    
    cout << "Master thread: Master thread exited" << endl;
}


