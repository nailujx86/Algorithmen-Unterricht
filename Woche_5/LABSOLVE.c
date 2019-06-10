#include <stdio.h>
#include <stdlib.h>

#define MAXCOLS 2048
#define MAXROWS 2048

typedef struct labyrinth {
    char lab[MAXCOLS + 2][MAXROWS];
    long costs[MAXCOLS][MAXROWS];
    long bestpath[MAXCOLS * MAXROWS][2];
    int maxcol;
    int maxrow;
    int startx;
    int starty;
    int treasurex;
    int treasurey;
} LabCell, *Lab_p;

int labInit(Lab_p lab) {
    int startFound, goalFound;
    startFound = goalFound = 0;
    lab->maxcol = 0;
    for (int i = 0; i < lab->maxrow; i++) {
        for (int j = 0; j < MAXCOLS; j++) {
            lab->costs[i][j] = 0;
            if ((lab->lab[i][j] == '\n') && (j > lab->maxcol)) {
                lab->maxcol = j;
            }
            if (lab->lab[i][j] == 'S') {
                if (!goalFound) {
                    lab->treasurex = i;
                    lab->treasurey = j;
                    goalFound = 1;
                    continue;
                } else {
                    printf("Fehler: Mehr als ein Ziel gefunden!");
                    return -1;
                }
            }
            if (lab->lab[i][j] == 'X') {
                if (!startFound) {
                    lab->startx = i;
                    lab->starty = j;
                    startFound = 1;
                    continue;
                } else {
                    printf("Fehler: Mehr als ein Start gefunden!");
                    return -1;
                }
            }
        }
    }
    if (!startFound) {
        printf("Fehler: Start nicht gefunden!");
        return -1;
    }
    if (!goalFound) {
        printf("Fehler: Ziel nicht gefunden!");
        return -1;
    }
    return 0;
}

Lab_p labRead(FILE *in) {
    Lab_p handle = malloc(sizeof(LabCell));
    char *inp;

    handle->maxrow = 0;
    while ((inp = fgets(handle->lab[handle->maxrow], MAXCOLS, in))) {
        handle->maxrow++;
        if (handle->maxrow > MAXROWS) {
            printf("Fehler: Labyrinth zu gross!");
            exit(EXIT_FAILURE);
        }
    }

    return handle;
}

void labPrint(FILE *out, Lab_p lab) {
    for (int i = 0; i < lab->maxrow; i++) {
        fprintf(out, "%s", lab->lab[i]);
    }
    fprintf(out, "\n");
}

void labPrintSolved(FILE *out, Lab_p lab) {
    for (int i = 0; i < lab->maxrow; i++) {
        for (int j = 0; j < lab->maxcol; j++) {
            fprintf(out, "%3d", lab->costs[i][j]);
        }
        fprintf(out, "\n");
    }
}

void labCalculateCosts(Lab_p lab, int x, int y, int count) {
    if (lab->costs[x][y]) {
        return;
    }
    lab->costs[x][y] = count;
    if (y + 1 < MAXCOLS - 1 && lab->lab[x][y + 1] != '#') {
        labCalculateCosts(lab, x, y + 1, count + 1);
    }
    if (y - 1 >= 0 && lab->lab[x][y - 1] != '#') {
        labCalculateCosts(lab, x, y - 1, count + 1);
    }
    if (x + 1 < MAXROWS - 1 && lab->lab[x + 1][y] != '#') {
        labCalculateCosts(lab, x + 1, y, count + 1);
    }
    if (x - 1 >= 0 && lab->lab[x - 1][y] != '#') {
        labCalculateCosts(lab, x - 1, y, count + 1);
    }
}

int labFindPath(Lab_p lab, int x, int y, int count) {
    if (lab->costs[lab->startx - 1][lab->starty] == 0 &&
        lab->costs[lab->startx + 1][lab->starty] == 0 &&
        lab->costs[lab->startx][lab->starty - 1] == 0 &&
        lab->costs[lab->startx][lab->starty + 1] == 0) {
        printf("Fehler: Kein Pfad gefunden!\n");
        return -1;
    }
    if (lab->costs[x - 1][y] != 0 && lab->costs[x - 1][y] < lab->costs[x][y]) {
        lab->bestpath[count][0] = x - 1;
        lab->bestpath[count][1] = y;
        return labFindPath(lab, x - 1, y, count + 1);
    }
    if (lab->costs[x + 1][y] != 0 && lab->costs[x + 1][y] < lab->costs[x][y]) {
        lab->bestpath[count][0] = x + 1;
        lab->bestpath[count][1] = y;
        return labFindPath(lab, x + 1, y, count + 1);
    }
    if (lab->costs[x][y - 1] != 0 && lab->costs[x][y - 1] < lab->costs[x][y]) {
        lab->bestpath[count][0] = x;
        lab->bestpath[count][1] = y - 1;
        return labFindPath(lab, x, y - 1, count + 1);
    }
    if (lab->costs[x][y + 1] != 0 && lab->costs[x][y + 1] < lab->costs[x][y]) {
        lab->bestpath[count][0] = x;
        lab->bestpath[count][1] = y + 1;
        return labFindPath(lab, x, y + 1, count + 1);
    }
    return 0;
}

int labFillPath(Lab_p lab) {
    int i;
    for(i = 0; i < lab->maxrow * lab->maxcol; i++) {
        if(lab->bestpath[i][0] == 0 && lab->bestpath[i][1] == 0)
            return i;
        if(lab->lab[lab->bestpath[i][0]][lab->bestpath[i][1]] != 'S' && lab->lab[lab->bestpath[i][0]][lab->bestpath[i][1]] != 'X')
            lab->lab[lab->bestpath[i][0]][lab->bestpath[i][1]] = '.';
    }
    return i;
}

int main(int argc, char *argv[]) {
    FILE *in = stdin;
    Lab_p lab;
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
    lab = labRead(in);
    labInit(lab);
    labPrint(stdout, lab);
    labCalculateCosts(lab, lab->treasurex, lab->treasurey, 1);
    labFindPath(lab, lab->startx, lab->starty, 0);
    printf("Pfadlaenge: %d\n", labFillPath(lab));
    labPrint(stdout, lab);
    /* Here: Read from in with (e.g.) fgets(), ... */
    if (in != stdin) {
        fclose(in);
    }
    exit(EXIT_SUCCESS);
}