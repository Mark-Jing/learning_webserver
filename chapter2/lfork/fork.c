#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid = fork();
    if(pid == -1) {
        perror("fork");
        return -1;
    }
    if (pid == 0) {
        printf("this is child process, pid = %d\n", getpid());
    } else if(pid > 0) {
        printf("this is parent process, pid = %d\n", getpid());
    }
    for(int i = 1; i <= 3; i++) {
        printf("i = %d, this is %s, pid = %d\n", i, pid == 0 ? "child process" : "parent process", getpid());
        sleep(2);
    }
    return 0;
}