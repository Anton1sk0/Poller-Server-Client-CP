#include <iostream>

#include "ArgumentManager.h"

using namespace std;

ArgumentManager::ArgumentManager() : port_num(-1), numWorkerThreads(-1), bufferSize(-1), poll_log(""), poll_stats("") {
}

ArgumentManager::~ArgumentManager() {
}

bool ArgumentManager::validate(int argc, char * argv[]) {
    if (argc != 6) {
        return false;
    }

    port_num = atoi(argv[1]);
    
    if (port_num == -1 || port_num == 0) {
        cerr << "Port number is missing \n";
        return false;
    }

    numWorkerThreads=atoi(argv[2]);
    
    if (numWorkerThreads <= 0) {
        cerr << "Number of working threads is missing \n";
        return false;
    }

    
    bufferSize=atoi(argv[3]);
    
    if (bufferSize <= 0) {
        cerr << "Buffer size is missing \n";
        return false;
    }

    poll_log=(argv[4]);
    
    if (poll_log == "") {
        cerr << "Poll log file is missing \n";
        return false;
    }

    poll_stats=(argv[5]);
    
    if (poll_stats == "") {
        cerr << "Poll stats file is missing \n";
        return false;
    }

    return true;
}