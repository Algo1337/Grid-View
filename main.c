#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <str.h>

#define LEFT_TOP_CORNER ""
#define RIGHT_TOP_CORNER ""
#define LEFT_BTTM_CORNER ""
#define RIGHT_BTTM_CORNER ""

#define VERITICAL_LINE "|"
#define HORIZONTAL_LINE "-"

typedef char * Column;

typedef struct Row {
    Column  **Columns;
} Row;

typedef struct Grid {
    int         RowCount;
    int         ColumnCount;
    int         ColumnSize;

    String      buff;
} Grid;

Grid InitGrid(int r, int c, int col_sz) {
    Grid g = { r, c, col_sz, NewString(NULL)};

    return g;
}

int CreateTitle(Grid *g, const char *q) {

    for(int i = 0; i < g->ColumnSize * g->ColumnCount + g->ColumnCount + 1; i++)
        g->buff.AppendString(&g->buff, HORIZONTAL_LINE);

    g->buff.AppendArray(&g->buff, (const char *[]){"\n", VERITICAL_LINE, " ", q, NULL});
    int spaces = g->ColumnSize * g->ColumnCount - (strlen(q) - 1);
    for(int i = 0; i < spaces; i++)
        g->buff.AppendString(&g->buff, " ");

    g->buff.AppendArray(&g->buff, (const char *[]){VERITICAL_LINE, "\n", NULL});
}

int CreateHeader(Grid *g, const char **arr) {
    if(!arr)
        return 0;

    for(int i = 0; i < g->ColumnSize * g->ColumnCount + g->ColumnCount + 1; i++)
        g->buff.AppendString(&g->buff, HORIZONTAL_LINE);

    g->buff.AppendArray(&g->buff, (const char *[]){"\n", VERITICAL_LINE, NULL});
    for(int i = 0; i < g->ColumnCount; i++) {
        g->buff.AppendArray(&g->buff, (const char *[]){" ", arr[i], NULL});
        for(int c = 0; c < g->ColumnSize - strlen(arr[i]) - 1; c++) {
            g->buff.AppendString(&g->buff, " ");
        }

        g->buff.AppendString(&g->buff, VERITICAL_LINE);
    }
    g->buff.AppendString(&g->buff, "\n");

    return 1;
}

int AddSeparator(Grid *g) {
    for(int i = 0; i < g->ColumnSize * g->ColumnCount + g->ColumnCount + 1; i++)
        g->buff.AppendString(&g->buff, HORIZONTAL_LINE);

    g->buff.AppendString(&g->buff, "\n");
}

int AddRow(Grid *g, const char **arr) {
    g->buff.AppendArray(&g->buff, (const char *[]){VERITICAL_LINE, NULL});
    for(int i = 0; i < g->ColumnCount; i++) {
        g->buff.AppendArray(&g->buff, (const char *[]){" ", arr[i], NULL});
        for(int c = 0; c < g->ColumnSize - strlen(arr[i]) - 1; c++) {
            g->buff.AppendString(&g->buff, " ");
        }

        g->buff.AppendString(&g->buff, VERITICAL_LINE);
    }
    g->buff.AppendString(&g->buff, "\n");
}

void DestroyGrid(Grid *g) {
    if(g->buff.data != NULL)
        g->buff.Destruct(&g->buff);

    free(g);
}

int main() {
    Grid g = InitGrid(3, 3, 10);
    
    CreateTitle(&g, "Testing");
    CreateHeader(&g, (const char *[]){"new", "gay", "fag"});
    
    AddSeparator(&g);
    AddRow(&g, (const char *[]){"new", "gay", "fag"});
    AddRow(&g, (const char *[]){"new", "gay", "fag"});
    AddRow(&g, (const char *[]){"new", "gay", "fag"});
    AddSeparator(&g);

    g.buff.data[g.buff.idx] = '\0';
    printf("%s\n", g.buff.data);

    g.Destruct(&g);
    return 0;
}
