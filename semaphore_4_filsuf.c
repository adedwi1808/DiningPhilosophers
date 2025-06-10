#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define N 5

sem_t forks[N];    // semaphore untuk setiap garpu
sem_t room;        // semaphore untuk membatasi maksimum 4 filsuf di meja

void* philosopher(void* num) {
    int id = *(int*)num;

    while (1) {
        printf("Philosopher %d is thinking...\n", id);
        sleep(1);

        sem_wait(&room);              // masuk ke ruang makan
        sem_wait(&forks[id]);         // ambil garpu kiri
        sem_wait(&forks[(id+1)%N]);   // ambil garpu kanan

        printf("Philosopher %d is eating...\n", id);
        sleep(1);

        sem_post(&forks[id]);         // letakkan garpu kiri
        sem_post(&forks[(id+1)%N]);   // letakkan garpu kanan
        sem_post(&room);              // keluar dari ruang makan
    }

    return NULL;
}

int main() {
    pthread_t threads[N];
    int ids[N];

    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1); // setiap garpu tersedia (1)
        ids[i] = i;
    }
    sem_init(&room, 0, N - 1); // maksimal 4 filsuf di ruang makan

    for (int i = 0; i < N; i++) {
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
