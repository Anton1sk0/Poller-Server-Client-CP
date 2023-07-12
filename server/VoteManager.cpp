#include "VoteManager.h"

using namespace std;

VoteManager::VoteManager(const char * output) : out(nullptr) {
    if (output != nullptr) {
        out = new ofstream(output);
    }
}

VoteManager::~VoteManager() {
    if (out != nullptr) {
        out->close();
        delete out;
    }
}

void VoteManager::add(string first_last_name, string vote) {
    lock_guard<std::mutex> lock(this->getMutex());  
    
    if (list.search(first_last_name) != "") {
        list.remove(first_last_name);
        list.add(first_last_name, vote);
    } else {
        list.add(first_last_name, vote);
    }
}

string VoteManager::getVote(string first_last_name) {
    lock_guard<std::mutex> lock(this->getMutex());
    string result = list.search(first_last_name);
    return result;
}

void VoteManager::remove(string first_last_name) {
    lock_guard<std::mutex> lock(this->getMutex());
    list.remove(first_last_name);
}

void VoteManager::print(ostream & out) {
    lock_guard<std::mutex> lock(this->getMutex());
    list.print(out);
}

int VoteManager::getLength() {
    lock_guard<std::mutex> lock(this->getMutex());
    return list.getCount();
}

string VoteManager::ToString() {
    lock_guard<std::mutex> lock(this->getMutex());
    return list.Tostring();
}

mutex& VoteManager::getMutex() {
    return mtxx;
}


void VoteManager::logToDisk(string first_last_name, string vote) {
    if (!out) {
        return;
    }
    
    lock_guard<std::mutex> lock(this->mtxx_output);
    
    (*out) << first_last_name << " " << vote << endl;
}