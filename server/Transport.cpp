#include "Transport.h"

#include <unistd.h>
#include <cstdio>
#include <cstring>

Transport::Transport() {
}

Transport::~Transport() {
}

int Transport::write_all(int fd, const char *buff, size_t size) {
    size_t sent;
    ssize_t n;

    for (sent = 0; sent < size; sent += n) {
        if ((n = write(fd, buff + sent, size - sent)) == -1) {
            perror("write");
            return -1; /* error */
        }
    }
    return sent;
}

int Transport::read_all(int fd, char *buff, size_t size) {
    size_t sent;
    ssize_t n;

    for (sent = 0; sent < size; sent += n) {
        if ((n = read(fd, buff + sent, size - sent)) == -1) {
            perror("write");
            return -1; /* error */
        }
    }
    return sent;
}


int Transport::write_all(int fd, const char *buff) {
    char buffer[MAX_BUFFER_SIZE];
    
    memset(buffer, 0, MAX_BUFFER_SIZE);
    
    strcpy(buffer, buff);
    
    return write_all(fd, buffer, MAX_BUFFER_SIZE);
}


int Transport::read_all(int fd, char *buff) {
    return read_all(fd, buff, MAX_BUFFER_SIZE);
}