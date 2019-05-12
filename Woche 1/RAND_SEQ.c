#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXNUM 1000

int main(int argc, char *argv[]) {
    FILE *in = stdin;
    char platz;
    int eingabe, num;
    //srand(time(0));

    if (argc > 3 || argc < 2) {
        fprintf(stderr, "Usage: %s [<num>]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    eingabe = atoi(argv[1]);

    for(int i = 0; i < eingabe; i++) {
        int num = rand() % MAXNUM;
        printf("%d\n", num);
    }

    exit(EXIT_SUCCESS);
}