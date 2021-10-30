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
    int i, j, grau = 0, aux;
    double den = 0;
    if (argc < 2)
    {
        exit(-1);
    }
    ent = argv[1];
    saida = (char *)malloc((strlen(argv[1]) + 1) * sizeof(char));
    if (ent == NULL || saida == NULL)
    {
        exit(-1);
    }
    strncpy(saida, ent, strlen(argv[1]) - 3);
    strcat(saida, "edge");
    if ((fp = fopen(ent, "r")) == NULL)
    {
        exit(-1);
    }
    if ((fp2 = fopen(saida, "w")) == NULL)
    {

        exit(-1);
    }
    g = (G *)calloc(1, sizeof(G));
    if (g == NULL)
    {
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
            if (g->table[i][j] != 0)
            {
                g->E++;
            }
        }
    }

    for (i = 0; i < (g->V); i++)
    {
        for (j = i + 1, aux = 0; j < (g->V); j++)
        {
            if (g->table[i][j] != 0)
            {
                aux++;
            }
        }
        if (grau < aux)
        {
            grau = aux;
        }
    }
    g->E /= 2;
    /*Densidade*/
    den = (double)(2 * g->E) / (g->V);
    printf("Densidade %.3f\t grau máximo %d\n", den, grau);
    fprintf(fp2, "Vertice:%d\tAresta:%d", g->V, g->E);
    for (i = 0; i < (g->V); i++)
    {
        for (j = i + 1, aux = 0; j < (g->V); j++)
        {
            if (g->table[i][j] != 0)
            {
                fprintf(fp2, "\n%d - %d Custo:%d", i, j, g->table[i][j]);
            }
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
