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
    ptr->payload = strdup(payload);
    ptr->next = NULL;
    return ptr;
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

void LinListRevert(LinList_p *anchor) {
    LinList_p newlist = NULL;
    LinList_p handle = NULL;
    while(*anchor) {
        handle = LinListExtractFirst(anchor);
        LinListInsertFirst(&newlist, handle);
    }
    *anchor = newlist;
}

void LinListPrint(LinList_p list) {
    while(list) {
        printf("\n%s", list->payload);
        list = list->next;
    }
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

int main(int argc, char const *argv[]) {
    LinList_p list = LinListAllocCell("ab");
    LinListInsertFirst(&list, LinListAllocCell("cd"));
    LinListInsertFirst(&list, LinListAllocCell("ef"));
    printf("%x", list);
    LinListPrint(list);
    getchar();
    return 0;
}
