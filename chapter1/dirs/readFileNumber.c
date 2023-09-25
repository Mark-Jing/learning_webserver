#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

int getFileNum(const char* path);

int main(int argc, char **argv) {
    if(argc < 2) {
        printf("%s path\n", argv[0]);
        return -1;
    }
    printf("%d\n", getFileNum(argv[1]));
    return 0;
}

int getFileNum(const char *path) {
    DIR *dir = opendir(path);
    if(dir == NULL) {
        perror("opendir");
        exit(0);
    }
    int total = 0;
    struct dirent *ptr;
    while((ptr = readdir(dir)) != NULL) {
        char *dname = ptr->d_name;
        if(strcmp(dname, ".") == 0 || strcmp(dname, "..") == 0) {
            continue;
        }
        if(ptr->d_type == DT_DIR) {
            char newpath[256];
            sprintf(newpath, "%s/%s", path, dname);
            total += getFileNum(newpath);
        }
        if(ptr->d_type == DT_REG) {
            total++;
        }
    }
    closedir(dir);
    return total;
}