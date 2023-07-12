#include <iostream>
#include <fstream>
#include <stdio.h>
#include <signal.h>
#include "VoteManager.h"
#include "PartyManager.h"
#include "ArgumentManager.h"
#include "ProducerConsumerQueue.h"
#include "WorkerThread.h"
#include "MasterThread.h"
#include <fstream>
#include <stdlib.h>
#include <signal.h>

void catchinterrupt(int signo) {
    cout << "exit activated \n";
}

void * startRoutineForMasterThread(void * arg) {
    MasterThread * thread = (MasterThread*) arg;
    thread->main();
    return NULL;
}

int main(int argc, char * argv[]) {
    ArgumentManager argManager;

    if (!argManager.validate(argc, argv)) {
        cerr << "invalid command line arguments \n";
        return EXIT_FAILURE;
    }

    PartyManager partyManager;
    VoteManager voteManager(argManager.poll_log.c_str());
    ProducerConsumerQueue queue(argManager.bufferSize);

    WorkerThread ** workerThreads = new WorkerThread*[argManager.numWorkerThreads];

    MasterThread masterThread(&argManager, &queue, workerThreads);

    static struct sigaction act;
    act.sa_handler = catchinterrupt;
    sigfillset(&(act.sa_mask));
    sigaction(SIGINT, &act, NULL);


    for (int i = 0; i < argManager.numWorkerThreads; i++) {
        workerThreads[i] = new WorkerThread(&argManager, &queue, &partyManager, &voteManager);
    }

    pthread_create(&masterThread.tid, NULL, startRoutineForMasterThread, &masterThread);

    cout << "MAIN THREAD: Waiting for master to exit \n";


    cout << "Press enter to shutdown the server" << endl;
    getchar();

    cout << "Exiting ... " << endl;

    masterThread.exit();

    pthread_join(masterThread.tid, NULL);


    for (int i = 0; i < argManager.numWorkerThreads; i++) {
        delete workerThreads[i];
    }

    delete [] workerThreads;
    
    ofstream fp(argManager.poll_stats.c_str());
    
    partyManager.print(fp);
       

    return 0;
}
