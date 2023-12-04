#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    for (int i=0; i<10; i++) {
        srand48(time(NULL) + i);
        printf("%f\n", drand48());
    }
    return 0;
}
