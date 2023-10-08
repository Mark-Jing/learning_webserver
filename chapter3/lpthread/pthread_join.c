#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

int value = 10;
void * callback(void * arg) {
    printf("thread id : %ld\n", pthread_self());
    sleep(2);
    pthread_exit((void *)(&value));
}

int main() {
    pthread_t tid;

    // 创建一个子线程
    int ret = pthread_create(&tid, NULL, callback, NULL);

    if(ret != 0) {
        char * errstr = strerror(ret);
        printf("error : %s\n", errstr);
    } 

    for(int i = 0; i < 5; i++) {
        printf("%d\n", i);
    }

    int* ret_val;
    int sta = pthread_join(tid, (void **)(&ret_val));

    printf("return value is %d\n", *ret_val);
    if(sta != 0) {
        char * errstr = strerror(sta);
        printf("pthread_join error: %s\n", errstr);
    } 

    pthread_exit(NULL);

    return 0;   // exit(0);
}