#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_fd == -1) {
        perror("socket");
        exit(-1);
    }

    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(9999);
    int ret = bind(listen_fd, (struct sockaddr*)&saddr, sizeof(saddr));
    if(ret == -1) {
        perror("bind");
        exit(-1);
    }

    ret = listen(listen_fd, 8);
    if(ret == -1) {
        perror("listen");
        exit(-1);
    }

    struct sockaddr_in clientaddr;
    int len = sizeof(clientaddr);
    int client_fd = accept(listen_fd, (struct sockaddr*)&clientaddr, &len);
    if(client_fd == -1) {
        perror("accept");
        exit(-1);
    }

    char clientIP[16];
    inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, clientIP, sizeof(clientIP));
    unsigned short clientport = ntohs(clientaddr.sin_port);
    printf("client ip is %s, client port is %d\n", clientIP, clientport);

    char recvBuf[1024] = {0};
    len = read(client_fd, recvBuf, sizeof(recvBuf));
    if(len < 0) {
        perror("read");
        exit(-1);
    } else if(len > 0) {
        printf("client sent \"%s\"\n", recvBuf);
        write(client_fd, recvBuf, strlen(recvBuf));
    } else {
        printf("client is closed\n");
    }

    close(client_fd);
    close(listen_fd);

    return 0;
}