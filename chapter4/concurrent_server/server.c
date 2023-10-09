#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <wait.h>

void recycleChild(int arg) {
    while(1) {
        int ret = waitpid(1, NULL, WNOHANG);
        if(ret == -1) {
            break;
        } else if(ret == 0) {
            break;
        } else if(ret > 0) {
            printf("child process %d is recycled.\n", ret);
        }
    }
}

int main() {
    struct sigaction act;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    act.sa_handler = recycleChild;
    sigaction(SIGCHLD, &act, NULL);

    int listen_fd = socket(PF_INET, SOCK_STREAM, 0);
    if(listen_fd == -1) {
        perror("socket");
        exit(-1);
    }

    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    saddr.sin_addr.s_addr = INADDR_ANY;

    int ret = bind(listen_fd, (struct sockaddr*)&saddr, sizeof(saddr));
    if(ret == -1) {
        perror("bind");
        exit(-1);
    }

    ret = listen(listen_fd, 128);
    if(ret == -1) {
        perror("listen");
        exit(-1);
    }

    while(1) {
        struct sockaddr_in client_addr;
        int len = sizeof(client_addr);
        int client_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &len);
        if(client_fd == -1) {
            if(errno == EINTR) {
                continue;
            }
            perror("accept");
            exit(-1);
        }

        pid_t pid = fork();
        if(pid == 0) {
            char clientIP[16];
            inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, clientIP, sizeof(clientIP));
            unsigned short client_port = ntohs(client_addr.sin_port);
            printf("client ip is %s, client port is %d\n",clientIP, client_port);

            char recv_buf[1024] = {0};
            while(1) {
                int len = read(client_fd, &recv_buf, sizeof(recv_buf));
                if(len == -1) {
                    perror("read");
                    exit(1);
                } else if(len > 0) {
                    printf("receive client data: %s\n", recv_buf);
                } else {
                    printf("client is closed\n");
                    break;
                }
                write(client_fd, recv_buf, strlen(recv_buf)+1);
            }
            close(client_fd);
            exit(0);
        } else if(pid == -1) {
            perror("fork");
            exit(-1);
        }
    }
    close(listen_fd);
    return 0;
}