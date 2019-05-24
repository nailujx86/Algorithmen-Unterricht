#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lin_list {
    char *payload;
    struct lin_list *next;
}LinListCell, *LinList_p;

LinList_p LinListAllocCell(char* payload) {
    LinListCell *ptr = (LinListCell*) malloc(sizeof(LinListCell));
    ptr->payload = payload;
    return ptr;
}

void LinListFreeCell(LinList_p junk) {
    free(junk);
    return;
}

void LinListFree(LinList_p *junk) {
    LinListFree(&(*junk)->next);
    free(*junk);
    *junk = NULL;
    return;
}

LinList_p LinListInsertFirst(LinList_p *anchor, LinList_p newcell) {
    newcell->next = *anchor;
    *anchor = newcell;
    return newcell;
}

LinList_p LinListExtractFirst(LinList_p *anchor) {
    if(*anchor) {
        LinList_p cur = *anchor;
        *anchor = cur->next;
        cur->next = NULL;
        return cur;
    }
    return NULL;
}

int main(int argc, char const *argv[]) {
    LinList_p list = LinListAllocCell("ab");
    LinListInsertFirst(&list, LinListAllocCell("cd"));
    LinListInsertFirst(&list, LinListAllocCell("ef"));
    printf("%x", list);
    return 0;
}
