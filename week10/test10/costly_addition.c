#include <stdlib.h>
#include <pthread.h>

void *increment_and_sleep(void *arg);

void costly_addition(int num) {

    if (num == 0) {
        return; 
    }

    pthread_t thread_id;

    pthread_create(&thread_id, NULL, increment_and_sleep, NULL);

    costly_addition(--num);
    pthread_join(thread_id, NULL);
}
