#ifndef VOTEMANAGER_H
#define VOTEMANAGER_H


#include <iostream>
#include <string>
#include <fstream>

#include "List.h"

using namespace std;
 
class VoteManager {
public:
    VoteManager(const char * output = NULL);
    virtual ~VoteManager();

    void add(string first_last_name, string vote);
    void remove(string first_last_name);
    string getVote(string first_last_name);
    int getLength();
    string ToString();
    mutex& getMutex();

    void print(ostream & out = cout);
    
    void logToDisk(string first_last_name, string vote);
private:
    List<string, string> list;
    mutex mtxx;
    mutex mtxx_output;
    ofstream * out;
};

#endif /* VOTEMANAGER_H */

