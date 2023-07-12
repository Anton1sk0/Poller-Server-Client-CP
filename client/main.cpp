#include <iostream>
#include <fstream>
#include <stdio.h>
#include <signal.h>
#include "ClientArgumentManager.h"
#include "ClientWorkerThread.h"
#include "ClientSocketManager.h"
#include "ClientWorkerThread.h"
#include "ClientThread.h"
#include "ClientMasterThread.h"
#include <fstream>
#include <stdlib.h>
#include <signal.h>
#include <cstdlib>
#include <cstring>
#include <fstream>

using namespace std;

void * startRoutineForMasterThread(void * arg) {
    MasterThread * thread = (MasterThread*) arg;
    thread->main();
    return NULL;
}
int main(int argc, char * argv[]) {
    ArgumentManager argman;
    
    if (!argman.validate(argc, argv)) {
        cerr << "invalid command line arguments \n";
        return EXIT_FAILURE;
    } else {
        cout << argman.serverName << ":" << argman.portNum << " => " << argman.poll_stats << endl;
    }
    
    ifstream input(argman.poll_stats.c_str());
    
    if (!input.is_open()) {
        cout << "File could not be opened \n" ;
        return 1;
    }
    
    int numThreads = 0;
    
    string line;
    
    while (input.good() && !input.eof() && getline(input, line)) {
        if (line != "") {
            numThreads++;
        }
    }    
    
    cout << "Total lines: " << numThreads << endl;


    MasterThread masterThread(argman.portNum, argman.serverName, numThreads, &argman);

    pthread_create(&masterThread.tid, NULL, startRoutineForMasterThread, &masterThread);
    pthread_join(masterThread.tid, NULL);
    
    return 0;
}

