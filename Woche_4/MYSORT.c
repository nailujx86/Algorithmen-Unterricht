#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Woche_3/LIN_LIST.c"

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
    char* inp;
    char curline[129];
    LinList_p list = LinListAllocCell("");
    while(inp = fgets(curline, 128, in)) {
        LinList_p c = LinListAllocCell(curline);
        LinListInsertLast(&list, c);
    }
    LinListExtractFirst(&list);
    LinListSort(&list);
    LinListPrint(list);

    getchar();
    /* Here: Read from in with (e.g.) fgets(), ... */
    if (in != stdin) {
        fclose(in);
    }
    exit(EXIT_SUCCESS);
}