#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include "WorkerThread.h"
#include "Transport.h"

using namespace std;

WorkerThread::WorkerThread(ArgumentManager * argumentManager, ProducerConsumerQueue * queue, PartyManager * partyManager, VoteManager * voteManager)
: argumentManager(argumentManager), queue(queue), partyManager(partyManager), voteManager(voteManager) {
    cout << "Worker thread created " << endl;
}

WorkerThread::~WorkerThread() {
    cout << "Worker thread destroyed " << endl;
}

void WorkerThread::main() {
    cout << "Worker thread started" << endl;

    while (true) {
        int fd = queue->obtain();

        cout << "Worker thread consumed fd: " << fd << endl;

        if (fd == -1) {
            break; // shutdown
        }

        process(fd);

        close(fd);
    }

    ////here make the result file??///

    cout << "Worker thread exited " << endl;
}

void WorkerThread::process(int fd) {
    const char* handshake = "SEND NAME PLEASE";
    const char* sendMeVoteMSG = "SEND VOTE PLEASE";
    const char* alreadyVotedMSG = "ALREADY VOTED";
    const char * reply;

    char buffer[MAX_BUFFER_SIZE];

    int bytesRead, bytesSent;

    if ((bytesSent = transport.write_all(fd, handshake)) < 0) {
        perror("handshake failed");
        return;
    }

    if ((bytesRead = transport.read_all(fd, buffer)) < 0) {
        perror("error with reading message");
        return;
    }

    cout << "message(name) from client " << buffer << endl;

    string nameForRegister = buffer; ///the name i want to register in database

    if (voteManager->getVote(nameForRegister) != "") {
        reply = alreadyVotedMSG;

        if (transport.write_all(fd, reply) < 0) {
            perror("failed to reply ");
            return;
        }
    } else {
        if ((bytesSent = transport.write_all(fd, sendMeVoteMSG)) < 0) {
            perror("handshake failed");
            return;
        }

        // Read the vote
        if ((bytesRead = transport.read_all(fd, buffer)) < 0) {
            perror("error with reading message");
            return;
        }

        cout << "message(vote) from client " << buffer << endl;

        string voteForRegister = buffer; //the vote i want to register in database     

        voteManager->add(nameForRegister, voteForRegister);
        
        cout << nameForRegister << " just voted for " << voteForRegister << endl;

        ////convert to string,append and back to char*////
        string nameString(nameForRegister);
        string voteString(voteForRegister);

        string replyStr = nameString + " just voted for " + voteString;
        const char* reply = replyStr.c_str();

        if (transport.write_all(fd, reply) < 0) {
            perror("failed to reply ");
            return;
        }
        
        partyManager->add(voteForRegister, 1);
        
        voteManager->logToDisk(nameForRegister, voteForRegister);
        
    }
}
