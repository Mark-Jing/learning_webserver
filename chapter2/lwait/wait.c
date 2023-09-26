#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    for(int i = 0; i < 5; i++) {
        pid = fork();
        if(pid == 0) {
            break;
        }
    }
    if(pid > 0) {
        while(1) {
            printf("parent, pid = %d\n", getpid());
            int st;
            int ret = wait(&st);
            if(ret == -1) {
                break;
            }
            if(WIFEXITED(st)) {
                printf("stat num: %d\n", WEXITSTATUS(st));
            }
            if(WIFSIGNALED(st)) {
                printf("killed by signal: %d\n", WTERMSIG(st));
            }
            printf("child dead, pid = %d\n", ret);
            sleep(1);
        }
    } else if(pid == 0) {
        while(1) {
            printf("child, pid = %d\n",getpid());
            sleep(1);
        }
    } else {
        perror("fork");
        return -1;
    }
    return 0;
}