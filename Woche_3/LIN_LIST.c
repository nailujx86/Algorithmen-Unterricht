#include "LIN_LIST.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LinList_p LinListAllocCell(char *payload) {
    LinListCell *ptr = (LinListCell *)malloc(sizeof(LinListCell));
    ptr->payload = strdup(payload);
    ptr->next = NULL;
    return ptr;
}

LinList_p LinListInsertFirst(LinList_p *anchor, LinList_p newcell) {
    newcell->next = *anchor;
    *anchor = newcell;
    return newcell;
}

LinList_p LinListInsertLast(LinList_p *anchor, LinList_p newcell) {
    LinList_p handle = *anchor;
    while (handle->next) {
        handle = handle->next;
    }
    handle->next = newcell;
    return *anchor;
}

LinList_p LinListExtractFirst(LinList_p *anchor) {
    if (*anchor) {
        LinList_p cur = *anchor;
        *anchor = cur->next;
        cur->next = NULL;
        return cur;
    }
    return NULL;
}

LinList_p LinListExtractLast(LinList_p *anchor) {
    if (*anchor) {
        LinList_p handle = *anchor;
        LinList_p before = *anchor;
        while (handle->next) {
            before = handle;
            handle = handle->next;
        }
        before->next = NULL;
        return handle;
    }
    return NULL;
}

LinList_p LinListExtract(LinList_p *anchor, LinList_p cell) {
    if (*anchor) {
        LinList_p handle = *anchor;
        LinList_p before = *anchor;
        while (handle && handle != cell) {
            before = handle;
            handle = handle->next;
        }
        if(!handle) {
            return NULL;
        }
        before->next = handle->next;
        return handle;
    }
    return NULL;
}

LinList_p LinListSort(LinList_p *anchor) {
    int sortCount;
    if (*anchor) {
        if(!&(*anchor)->next) {
            return *anchor;
        }
        do {
            sortCount = 0;
            LinList_p handle = *anchor;
            LinList_p before = *anchor;
            while(handle->next) {
                if(strcmp(handle->payload, handle->next->payload) > 0) {
                    sortCount++;
                    before->next = handle->next->next;
                    handle->next = before->next;
                    break;
                } else {
                    before = handle;
                    handle = handle->next;
                }
            }
        } while (sortCount != 0);
    }
    return NULL;
}

LinList_p LinListFind(LinList_p *anchor, char *payload) {
    if (*anchor) {
        LinList_p handle = *anchor;
        while (handle) {
            if (!strcmp(handle->payload, payload)) {
                return handle;
            }
            handle = handle->next;
        }
        return NULL;
    }
    return NULL;
}

void LinListRevert(LinList_p *anchor) {
    LinList_p newlist = NULL;
    LinList_p handle = NULL;
    while (*anchor) {
        handle = LinListExtractFirst(anchor);
        LinListInsertFirst(&newlist, handle);
    }
    *anchor = newlist;
}

void LinListPrint(LinList_p list) {
    while (list) {
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
