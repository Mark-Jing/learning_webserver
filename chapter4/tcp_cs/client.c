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

    char* data = "hello, i am client";
    write(client_fd, data, strlen(data));

    char recvBuf[1024] = {0};
    int len = read(client_fd, recvBuf, sizeof(recvBuf));
    if(len < 0) {
        perror("read");
        exit(-1);
    } else if(len > 0) {
        printf("server sent %s\n", recvBuf);
    } else {
        printf("server is closed\n");
    }

    close(client_fd);

    return 0;
}