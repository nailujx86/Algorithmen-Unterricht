#ifndef LIST_HEADER
#define LIST_HEADER

typedef struct lin_list {
    char *payload;
    struct lin_list *next;
}LinListCell, *LinList_p;

LinList_p LinListAllocCell(char* payload);
LinList_p LinListInsertFirst(LinList_p *anchor, LinList_p newcell);
LinList_p LinListInsertLast(LinList_p *anchor, LinList_p newcell);
LinList_p LinListExtractFirst(LinList_p *anchor);
LinList_p LinListExtractLast(LinList_p *anchor);
LinList_p LinListExtract(LinList_p *anchor, LinList_p cell);
LinList_p LinListSort(LinList_p *anchor);
LinList_p LinListFind(LinList_p *anchor, char* payload);
void LinListRevert(LinList_p *anchor);
void LinListPrint(LinList_p list);
void LinListFreeCell(LinList_p junk);
void LinListFree(LinList_p *junk);

#endif