#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXITEMS 10000

int main(int argc, char *argv[]) {
    FILE *in = stdin;

    if (argc > 2) {
        fprintf(stderr, "Usage: %s [<file>]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (argc == 2) {
        in = fopen(argv[1], "r");
        if (!in) {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    
    char lineList[MAXITEMS][129];
    int lineCounter = 0;
    char line[129];

    while (fgets(line, 128, in)) {
        strcpy(lineList[lineCounter], line);
        lineCounter++;
    }

    for(int i = lineCounter - 1; i >= 0; i--) {
        printf(lineList[i]);
    } 

    if (in != stdin) {
        fclose(in);
    }
    exit(EXIT_SUCCESS);
}