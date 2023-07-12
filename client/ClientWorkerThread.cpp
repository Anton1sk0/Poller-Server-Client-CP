#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include "ClientWorkerThread.h"
#include "Transport.h"

#define MAX_BUFFER_SIZE 1024

using namespace std;

WorkerThread::WorkerThread(SocketManager *socketManager, string line) : socketManager(socketManager), line(line) {
    cout << "Worker thread created " << endl;
}

WorkerThread::~WorkerThread() {
    cout << "Worker thread destroyed " << endl;
}

void WorkerThread::main() {
    cout << "Worker thread started for line: " << line << endl;

    socketManager->open();
    socketManager->connect();

    int fd = socketManager->getSocket();

    process(fd);

    socketManager->close();

    cout << "Worker thread exited " << endl;
}

void WorkerThread::process(int fd) {
    const char* handshake = "SEND NAME PLEASE";
    const char* sendMeVoteMSG = "SEND VOTE PLEASE";
    const char* alreadyVotedMSG = "ALREADY VOTED";
    string sendVotersName = getNameFromLine(line);
    string sendVote = getVoteFromLine(line);

    char buffer[MAX_BUFFER_SIZE] = {0};

    int bytesRead, bytesSent;

    if ((bytesRead = transport.read_all(fd, buffer)) < 0 || strcmp(buffer, handshake) != 0) {
        perror("error with reading message");
        printf("handshake: %s \n", buffer);
        return;
    }

    cout << "message(name) from server " << buffer << endl;

    if (transport.write_all(fd, sendVotersName.c_str()) < 0) {
        perror("failed to reply :send vote please ");
        return;
    }

    if ((bytesRead = transport.read_all(fd, buffer)) < 0) {
        perror("error with reading message");
        printf("handshake: %s \n", buffer);
        return;
    }

    if (strcmp(buffer, alreadyVotedMSG) == 0) {
        printf("ERROR: already voted \n");
        return;
    }

    if (strcmp(buffer, sendMeVoteMSG) != 0) {
        perror("error with reading message");
        printf("handshake: %s \n", buffer);
        return;
    }

    cout << "message(vote) from server " << buffer << endl;

    if (transport.write_all(fd, sendVote.c_str()) < 0) {
        perror("failed to reply :send vote please ");
        return;
    }

    if ((bytesRead = transport.read_all(fd, buffer)) < 0) {
        perror("error with reading message");
        printf("handshake: %s \n", buffer);
        return;
    }

    std::cout << "Message from server: " << buffer << std::endl;
}

string WorkerThread::getNameFromLine(string line) {
    stringstream ss(line);
    string firstname;
    string lastname;
    string party;

    std::getline(ss, firstname, ' ');
    std::getline(ss, lastname, ' ');
    std::getline(ss, party, ' ');
    
    return firstname + " " + lastname;
}

string WorkerThread::getVoteFromLine(string line) {
    stringstream ss(line);
    string firstname;
    string lastname;
    string party;

    std::getline(ss, firstname, ' ');
    std::getline(ss, lastname, ' ');
    std::getline(ss, party, ' ');
    
    return party;
    
}

