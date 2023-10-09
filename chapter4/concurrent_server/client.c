#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(client_fd == -1) {
        perror("socket");
        exit(-1);
    }

    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &saddr.sin_addr.s_addr);
    saddr.sin_port = htons(9999);
    int ret = connect(client_fd, (struct sockaddr*)&saddr, sizeof(saddr));
    if(ret == -1) {
        perror("connect");
        exit(-1);
    }

    char recv_buf[1024] = {0};
    int i = 0;
    while(1) {
        sprintf(recv_buf, "data : %d\n", i++);
        write(client_fd, recv_buf, strlen(recv_buf)+1);

        int len = read(client_fd, recv_buf, sizeof(recv_buf));
        if(len == -1) {
            perror("read");
            exit(-1);
        } else if(len > 0) {
            printf("receive server data : %s\n", recv_buf);
        } else if(len == 0) {
            printf("server is closed");
            break;
        }
        sleep(1);
    }

    close(client_fd);

    return 0;
}