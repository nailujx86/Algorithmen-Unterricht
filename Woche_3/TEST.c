#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "LIN_LIST.c"

int main(int argc, char const *argv[]) {
    LinList_p list = LinListAllocCell("ab");
    LinListInsertFirst(&list, LinListAllocCell("cd"));
    LinListInsertFirst(&list, LinListAllocCell("ef"));
    printf("%x", list);
    LinListPrint(list);
    getchar();
    return 0;
}