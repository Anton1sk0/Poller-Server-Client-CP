#include <iostream>
#include <fstream>

#include "ClientMasterThread.h"
#include "ClientSocketManager.h"

using namespace std;

void * startRoutineForWorkerThread(void * arg) {
    WorkerThread * thread = (WorkerThread*) arg;
    thread->main();
    
    return NULL;
}

MasterThread::MasterThread(int portNum, string serverName, int numThreads, ArgumentManager * argumentManager) : portNum(portNum), serverName(serverName), numThreads(numThreads), argumentManager(argumentManager), workerThreads(workerThreads) {
    cout << "Master thread created " << endl;
    
    workerThreads = new WorkerThread*[numThreads]();
}

MasterThread::~MasterThread() {
    cout << "Master thread destroyed " << endl;
    
    for (int i = 0; i < numThreads; ++i) {
        delete workerThreads[i];
    }
    delete[] workerThreads;
}

void MasterThread::main() {
    cout << "Master thread started" << endl;

    SocketManager** socks = new SocketManager*[numThreads]; //for deallocate later

    ifstream input(argumentManager->poll_stats.c_str());
    
    for (int i = 0; i < numThreads; i++) {
        string line;
        
        getline(input, line);
        
        cout << "Master thread: Creating worker thread " << i << " for line: " << line << endl;

        socks[i] = new SocketManager(argumentManager->portNum, argumentManager->serverName);

        workerThreads[i] = new WorkerThread(socks[i], line);
        
        pthread_create(&workerThreads[i]->tid, NULL, startRoutineForWorkerThread, workerThreads[i]);

    }

    for (int i = 0; i < numThreads; ++i) {
        pthread_join(workerThreads[i]->tid, NULL);
        delete socks[i];
    }
    
    delete[] socks;

    cout << "Master thread exited " << endl;
}


