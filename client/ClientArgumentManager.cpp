#include <iostream>
#include "ClientArgumentManager.h"

using namespace std;

ArgumentManager::ArgumentManager() : portNum(-1), serverName(""), poll_stats("") {
}

ArgumentManager::~ArgumentManager() {
}

bool ArgumentManager::validate(int argc, char * argv[]) {
    if (argc != 4) {
        return false;
    }

    serverName = (argv[1]);

    if (serverName == "") {
        cerr << "server name is missing \n";
        return false;
    }

    
    portNum = atoi(argv[2]);

    if (portNum == -1) {
        cerr << "Port number is missing \n";
        return false;
    }
    
    poll_stats = (argv[3]);

    if (poll_stats == "") {
        cerr << "input file is missing \n";
        return false;
    }


    return true;
}
