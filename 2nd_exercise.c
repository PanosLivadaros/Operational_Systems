#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 4
const char *messages[] = {"Hello ", "there ", "wonderful ", "world!\n"};

sem_t semaphores[NUM_THREADS]; // Semaphore array for synchronization

// Function executed by each thread
void* print_message(void* arg) {
    int index = *(int*)arg; // Get thread's index from argument
    while (1) {
        sem_wait(&semaphores[index]); // Wait for semaphore signal to print
        printf("%s", messages[index]); // Print the assigned message
        fflush(stdout); // Ensure immediate output
        sem_post(&semaphores[(index + 1) % NUM_THREADS]); // Signal next thread
    }
}

int main() {
    pthread_t threads[NUM_THREADS];
    int indices[NUM_THREADS];

    // Initialize semaphores: First thread starts with 1, others start with 0
    for (int i = 0; i < NUM_THREADS; i++) {
        sem_init(&semaphores[i], 0, (i == 0) ? 1 : 0);
        indices[i] = i;
        pthread_create(&threads[i], NULL, print_message, &indices[i]);
    }

    // Join all threads, though they run infinitely
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        sem_destroy(&semaphores[i]);
    }

    return 0; // Program should never actually reach here
}
