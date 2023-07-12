#include "PartyManager.h"
using namespace std;

PartyManager::PartyManager() {
}

PartyManager::~PartyManager() {
}

void PartyManager::add(string party, int total_votes) {
    lock_guard<std::mutex> lock(this->getMutex());

    if (list.search(party) != -1) {
        int n = list.search(party) + 1;
        
        list.remove(party);
        list.add(party, n);
    } else {
        list.add(party, total_votes);
    }
}

int PartyManager::getVote(string party) {
    lock_guard<std::mutex> lock(this->getMutex());
    return list.search(party);
}

void PartyManager::remove(string party) {
    lock_guard<std::mutex> lock(this->getMutex());
    list.remove(party);
}

void PartyManager::print(ostream & out) {
    lock_guard<std::mutex> lock(this->getMutex());
    list.print(out);
}

int PartyManager::getLength() {
    lock_guard<std::mutex> lock(this->getMutex());
    return list.getCount();
}

mutex& PartyManager::getMutex() {
    return mtxx;
}

/*string PartyManager::ToString(){
   return list.Tostring();
}*/
