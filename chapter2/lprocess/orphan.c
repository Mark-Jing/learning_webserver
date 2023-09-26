#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    if(pid == 0) {
        printf("in parent process, pid = %d, ppid = %d\n", getpid(), getppid());
    } else if(pid > 0) {
        printf("in child process, pid = %d, ppid = %d\n",getpid(), getppid());
        sleep(3);
    }
    printf("hello, pid = %d, ppid = %d\n",getpid(), getppid());
    return 0;
}