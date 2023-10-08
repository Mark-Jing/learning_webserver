#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int num = 1;
pthread_rwlock_t rwlock;

void* write_num(void* arg) {
    while(1) {
        pthread_rwlock_wrlock(&rwlock);
        num++;
        printf("write, tid: %ld, num: %d\n", pthread_self(), num);
        pthread_rwlock_unlock(&rwlock);
        usleep(100);
    }
    return NULL;
}

void* read_num(void* arg) {
    while(1) {
        pthread_rwlock_rdlock(&rwlock);
        printf("read, tid: %ld, num: %d\n", pthread_self(), num);
        pthread_rwlock_unlock(&rwlock);
        usleep(100);
    }
    return NULL;
}

int main() {
    pthread_rwlock_init(&rwlock, NULL);
    pthread_t wtids[3], rtids[5];
    for(int i = 0; i < 3; i++) {
        pthread_create(&wtids[i], NULL, write_num, NULL);
    }
    for(int i = 0; i < 5; i++) {
        pthread_create(&rtids[i], NULL, read_num, NULL);
    }
    for(int i = 0; i < 3; i++) {
        pthread_detach(wtids[i]);
    }
    for(int i = 0; i < 5; i++) {
        pthread_detach(rtids[i]);
    }
    pthread_rwlock_destroy(&rwlock);
    pthread_exit(NULL);
}