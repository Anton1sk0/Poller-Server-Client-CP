#ifndef PRODUCERCONSUMERQUEUE_H
#define PRODUCERCONSUMERQUEUE_H

#include <pthread.h>

class ProducerConsumerQueue {
public:
    ProducerConsumerQueue(int POOL_SIZE);
    virtual ~ProducerConsumerQueue();

    void place(int data);

    int obtain();

private:
    int POOL_SIZE;

    struct {
        int * data;
        int start;
        int end;
        int count;
    } pool;

    pthread_mutex_t mtx;
    pthread_cond_t cond_nonempty;
    pthread_cond_t cond_nonfull;
};

#endif /* PRODUCERCONSUMERQUEUE_H */

