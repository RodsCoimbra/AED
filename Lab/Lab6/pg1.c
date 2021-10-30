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
    ent = (char *)malloc((strlen(argv[1]) + 2) * sizeof(char));
    if (ent == NULL)
    {
        exit(-1);
    }
    strcpy(ent, argv[1]);
    if ((fp = fopen(ent, "r")) == NULL)
    {
        exit(-1);
    }
    saida = strrchr(ent, '.');
    *saida = '\0';
    strcat(ent, ".edge");
    if ((fp2 = fopen(ent, "w")) == NULL)
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
        g->table[i] = (int *)calloc(1, sizeof(int) * (g->V));
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
    fprintf(fp2, "%d %d", g->V, g->E);
    for (i = 0; i < (g->V); i++)
    {
        for (j = i + 1, aux = 0; j < (g->V); j++)
        {
            if (g->table[i][j] != 0)
            {
                fprintf(fp2, "\n%d %d %d", i, j, g->table[i][j]);
            }
        }
    }

    fclose(fp);
    fclose(fp2);
    free(ent);
    for (i = 0; i < g->V; i++)
    {
        free(g->table[i]);
    }
    free(g->table);
    free(g);
    return 0;
}
