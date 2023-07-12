
#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <thread>


class Thread {
public:
    Thread();
    virtual ~Thread();
    
    pthread_t tid;
};

#endif /* CLIENTTHREAD_H */

