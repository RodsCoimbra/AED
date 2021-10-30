#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista_de_adjacencia
{
    ladj *next;
    int custo;
} ladj;

typedef struct garfo
{
    ladj **table;
    int V; /*vertices*/
    int E; /*Arestas*/
} G;

ladj *criar(int custo, ladj *g)
{
    ladj *novo = g, *aux;
    novo = (ladj *)malloc(sizeof(ladj));
    if (novo != NULL)
    {
        for (aux = g; aux->next != NULL; aux = aux->next)
            ;
        aux->next = novo;
    }
    else
    {
        return novo;
    }
    novo->next = NULL;
    novo->custo = custo;
    return g;
}

int main(int argc, char *argv[])
{
    FILE *fp, *fp2;
    char *ent, *saida;
    G *g;
    int i, j, aux;
    ladj *aux2;
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
    strncpy(saida, ent, strlen(argv[1]) - 4);
    strcat(saida, "ladj");
    if ((fp = fopen(ent, "r")) == NULL)
    {
        exit(-1);
    }
    if ((fp2 = fopen(saida, "w")) == NULL)
    {

        exit(-1);
    }
    g = (G *)malloc(sizeof(G));
    if (g == NULL)
    {
        exit(-1);
    }
    fscanf(fp, "%d", &g->V);
    g->table = (ladj **)calloc(1, sizeof(ladj *) * (g->V));

    for (i = 0; i < (g->V); i++)
    {
        for (j = 0; j < (g->V); j++)
        {
            fscanf(fp, "%d", &aux);
            if (aux != 0)
            {
                g->table[i] = criar(aux, g->table[i]);
                g->E++;
            }
        }
    }
    g->E /= 2;
    for (i = 0; i < (g->V); i++)
    {
        for (aux2 = g->table[i]; aux2 != NULL; aux2 = aux2->next)
        {
            printf("%d", aux2->custo);
        }
        printf("\n");
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