// Tested by [Brandon Chikandiwa (z5495844) on 19/04/2024]
//! fix the data race in the below program!


/// You are permitted to add standard headers (useful for atomics)
#include <pthread.h>
#include <stdatomic.h>

/// You are permitted to modify the type of
/// this global variable (useful for atomics)
atomic_int global_counter = 0;

/// You are permitted to create another global
/// variable (useful for mutex)


/// You are permitted to modify this function
/// (will be necessary for both mutex and atomics)
void perform_increment(void) {
    global_counter++;
}


///
/// DO NOT CHANGE ANY CODE BELOW THIS POINT
///

void *thread_run(void *data) {
    int n_increments = * (int *) data;

    for (int i = 0; i < n_increments; i++) {
        perform_increment();
    }

    return NULL;
}


int get_global_counter(void) {
    return global_counter;
}
