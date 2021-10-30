#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct garfo
{
    int **table;
    int V; /*vertices*/
    int E; /*Arestas*/
} G;

int main(int argc, char *argv[])
{
    FILE *fp, *fp2;
    char *ent, *saida;
    G *g;
    int i, j;
    if (argc < 2)
    {
        printf("Entrei1");
        exit(-1);
    }
    ent = argv[1];
    saida = (char *)malloc((strlen(argv[1]) + 1) * sizeof(char));
    if (ent == NULL || saida == NULL)
    {
        printf("Entrei2");
        exit(-1);
    }
    strncpy(saida, ent, strlen(argv[1]) - 3);
    strcat(saida, "edge");
    printf("%s", ent);
    if ((fp = fopen(ent, "r")) == NULL)
    {
        printf("Entrei3");
        exit(-1);
    }
    if ((fp2 = fopen(saida, "w")) == NULL)
    {

        printf("Entrei4");
        exit(-1);
    }
    g = (G *)calloc(1, sizeof(G));
    if (g == NULL)
    {
        printf("Entrei5");
        exit(-1);
    }
    fscanf(fp, "%d", &g->V);
    g->table = (int **)malloc(sizeof(int *) * (g->V));
    for (i = 0; i < g->V; i++)
    {
        g->table[i] = (int *)malloc(sizeof(int) * (g->V));
    }
    for (i = 0; i < (g->V); i++)
    {
        for (j = 0; j < (g->V); j++)
        {
            fscanf(fp, "%d", &(g->table[i][j]));
        }
    }
    for (i = 0; i < (g->V); i++)
    {
        for (j = 0; j < (g->V); j++)
        {
            printf("%d", g->table[i][j]);
        }
    }
    fclose(fp);
    fclose(fp2);
    free(saida);
    for (i = 0; i < g->V; i++)
    {
        free(g->table[i]);
    }
    free(g->table);
    free(g);
    return 0;
}
