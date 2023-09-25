#include <stdio.h>

#define PI 3.14

int main() {
    // this is test
    double sum = PI + 10;
#ifdef DEBUG
    printf("hello world!\n");
#endif
    printf("hello gcc!\n");
    return 0;
}