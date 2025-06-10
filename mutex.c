#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define N 5

pthread_mutex_t forks[N];

void* philosopher(void* num) {
    int id = *(int*)num;

    while (1) {
        printf("Philosopher %d is thinking...\n", id);
        sleep(1);

        // Deadlock-prone: semua filsuf bisa ambil garpu kiri bersamaan
        pthread_mutex_lock(&forks[id]);         // ambil garpu kiri

        //Uncomment Jika ingin memaksa deadlock
        //sleep(1); // jeda agar semua sempat ambil garpu kiri

        pthread_mutex_lock(&forks[(id+1)%N]);   // ambil garpu kanan

        printf("Philosopher %d is eating...\n", id);
        sleep(1);

        pthread_mutex_unlock(&forks[id]);       // letakkan garpu kiri
        pthread_mutex_unlock(&forks[(id+1)%N]); // letakkan garpu kanan
    }

    return NULL;
}

int main() {
    pthread_t threads[N];
    int ids[N];

    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&forks[i], NULL);
        ids[i] = i;
    }

    for (int i = 0; i < N; i++) {
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
