#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

sem_t empty;   // Semaphore for empty slots in buffer
sem_t full;    // Semaphore for full slots in buffer
pthread_mutex_t mutex; // Mutex for mutual exclusion

// Producer function
void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 100; // Produce a random item
        sem_wait(&empty); // Wait for an empty slot
        pthread_mutex_lock(&mutex); // Enter critical section

        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE; // Circular buffer update

        pthread_mutex_unlock(&mutex); // Leave critical section
        sem_post(&full); // Signal that there's a new item to consume

        sleep(1); // Simulate production delay
    }
}

// Consumer function
void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(&full); // Wait for a full slot
        pthread_mutex_lock(&mutex); // Enter critical section

        item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE; // Circular buffer update

        pthread_mutex_unlock(&mutex); // Leave critical section
        sem_post(&empty); // Signal that there's a new empty slot

        sleep(2); // Simulate consumption delay
    }
}

int main() {
    pthread_t prod, cons;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE); // Empty slots initially = buffer size
    sem_init(&full, 0, 0); // Full slots initially = 0
    pthread_mutex_init(&mutex, NULL); // Initialize mutex

    // Create producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for threads to finish (this will not happen because of the infinite loop)
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Cleanup resources (unreachable in this infinite loop)
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
