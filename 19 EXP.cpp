#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock;
int counter = 0;

void *threadFunc(void *arg) {
    int id = *((int *)arg);  // safe extraction of thread id

    pthread_mutex_lock(&lock);

    counter++;
    printf("Thread %d entered | Counter = %d\n", id, counter);
    sleep(1);
    printf("Thread %d exiting\n", id);

    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    pthread_t t1, t2, t3;

    int id1 = 1, id2 = 2, id3 = 3;

    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, threadFunc, &id1);
    pthread_create(&t2, NULL, threadFunc, &id2);
    pthread_create(&t3, NULL, threadFunc, &id3);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    pthread_mutex_destroy(&lock);

    return 0;
}
