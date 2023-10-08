#include <stdio.h>
#include <pthread.h>

int tickets = 100;
pthread_mutex_t mutex;

void* sellticket(void* arg) {
    while(1) {
        pthread_mutex_lock(&mutex);
        if(tickets > 0) {
            printf("%ld is selling %d - th ticket.\n", pthread_self(), tickets);
            tickets--;
        } else {
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);
    }
}

int main() {
    pthread_mutex_init(&mutex, NULL);

    pthread_t tid1, tid2, tid3;
    pthread_create(&tid1, NULL, sellticket, NULL);
    pthread_create(&tid2, NULL, sellticket, NULL);
    pthread_create(&tid3, NULL, sellticket, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    pthread_exit(NULL);
    return 0;
}