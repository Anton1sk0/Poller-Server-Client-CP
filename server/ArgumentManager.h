
#ifndef ARGUMENTMANAGER_H
#define ARGUMENTMANAGER_H

#include <string>

using namespace std;

class ArgumentManager {
public:
    int port_num;
    int numWorkerThreads;
    int bufferSize;
    string poll_log;
    string poll_stats;
    
    ArgumentManager();
    virtual ~ArgumentManager();
    
    bool validate(int argc, char * argv[]);      
    
    
};

#endif /* ARGUMENTMANAGER_H */

