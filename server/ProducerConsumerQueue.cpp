#include "ProducerConsumerQueue.h"

ProducerConsumerQueue::ProducerConsumerQueue(int POOL_SIZE) : POOL_SIZE(POOL_SIZE) {
    pool.start = 0;
    pool.end = -1;
    pool.count = 0;
    pool.data = new int[POOL_SIZE];
            
    pthread_mutex_init(&mtx, 0);
    pthread_cond_init(&cond_nonempty, 0);
    pthread_cond_init(&cond_nonfull, 0);
}

ProducerConsumerQueue::~ProducerConsumerQueue() {
    pthread_cond_destroy(&cond_nonempty);
    pthread_cond_destroy(&cond_nonfull);
    pthread_mutex_destroy(&mtx);
    
    delete [] pool.data;
}

void ProducerConsumerQueue::place(int data) {
    pthread_mutex_lock(&mtx);
    
    while (pool.count == POOL_SIZE) {
        pthread_cond_wait(&cond_nonfull, &mtx);
    }
    
    pool.end = (pool.end + 1) % POOL_SIZE;
    pool.data[pool.end] = data;
    pool.count++;

    pthread_cond_signal(&cond_nonempty);

    pthread_mutex_unlock(&mtx);
}

int ProducerConsumerQueue::obtain() {
    int data = 0;

    pthread_mutex_lock(&mtx);

    while (pool.count == 0) {
        pthread_cond_wait(&cond_nonempty, &mtx);
    }
    
    data = pool.data[pool.start];
    pool.start = (pool.start + 1) % POOL_SIZE;
    pool.count--;

    pthread_cond_signal(&cond_nonfull);
    
    pthread_mutex_unlock(&mtx);

    return data;
}
