#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <cstdlib>

#define MAX_BUFFER_SIZE 1024

class Transport {
public:
    Transport();
    virtual ~Transport();

    int write_all(int fd, const char *buff, size_t size);
    
    int read_all(int fd, char *buff, size_t size);
    
    int write_all(int fd, const char *buff);
    
    int read_all(int fd, char *buff);
};

#endif /* TRANSPORT_H */

