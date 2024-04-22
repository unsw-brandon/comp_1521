// Tested by [Brandon Chikandiwa (z5495844) on 19/04/2024]
#include "thread_chain.h"
#include <pthread.h>
#include <stdio.h>

void *my_thread(void *data) {
    thread_hello();

    int *n = data;
    if ((*n) < 49) {
        (*n)++;
        pthread_t thread_handle;
        pthread_create(&thread_handle, NULL, my_thread, data);
        pthread_join(thread_handle, NULL);
    }

    return NULL;
}

void my_main(void) {
    int n = 0;
    pthread_t thread_handle;
    pthread_create(&thread_handle, NULL, my_thread, &n);
    pthread_join(thread_handle, NULL);
}
