#ifndef PARTYMANAGER_H
#define PARTYMANAGER_H

#include <ostream>
#include <string>

#include "List.h"

using namespace std;

class PartyManager {
public:
    PartyManager();
    virtual ~PartyManager();

    void add(string party, int total_votes);
    void remove(string party);
    int getVote(string party);
    int getLength();
    //string ToString();

    void print(ostream & out = cout);
    mutex& getMutex();
private:
    List<string, int> list;
    mutex mtxx;
};

#endif /* PARTYMANAGER_H */

