#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int pipefd[2];
    // pipefd[0] is the read end.
    int ret = pipe(pipefd);
    if(ret == -1) {
        perror("pipe");
        return -1;
    }
    pid_t pid = fork();
    if(pid > 0) {
        char *msg = "hello, this is parent process";
        write(pipefd[1], "hello, this is parent process", sizeof(msg));
    } else if(pid == 0) {
        char buf[1024] = {0};
        int len = read(pipefd[0], buf, sizeof(buf));
        printf("child received: %s, pid = %d\n", buf, getpid());
    }
    return 0;
}