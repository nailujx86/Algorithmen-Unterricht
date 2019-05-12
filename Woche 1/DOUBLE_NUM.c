#include <stdio.h>
#include <stdlib.h>

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

    char line[129];

    while (fgets(line, 128, in)) {
        long int lineNum = strtol(line, NULL, 10);
        if (lineNum) {
            printf("%ld\n", lineNum * 2);
        }
    }

    /* Here: Read from in with (e.g.) fgets(), ... */
    if (in != stdin) {
        fclose(in);
    }
    exit(EXIT_SUCCESS);
}