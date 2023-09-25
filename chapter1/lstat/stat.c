#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    struct stat statbuf;
    int ret = stat("a.txt", &statbuf);
    if(ret == -1) {
        perror("stat");
        return -1;
    }
    printf("%ld\n", statbuf.st_atime);
    return 0;
}