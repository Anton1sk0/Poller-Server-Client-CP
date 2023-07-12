#ifndef THREAD_H
#define THREAD_H

#include <thread>


class Thread {
public:
    Thread();
    virtual ~Thread();
    
    pthread_t tid;
};

#endif /* THREAD_H */

