#ifndef ClientArgumentManager_H
#define ClientArgumentManager_H

#include <string>

using namespace std;

class ArgumentManager {
public:
    int portNum;
    string serverName;
    string poll_stats;
    
    ArgumentManager();
    virtual ~ArgumentManager();
    
    bool validate(int argc, char * argv[]);      
    
    
};

#endif /* ClientArgumentManager_H */

