#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista_de_adjacencia
{
    struct lista_de_adjacencia *next;
    int no;
    int custo;
} ladj;

typedef struct garfo
{
    ladj **table;
    int V; /*vertices*/
    int E; /*Arestas*/
} G;

ladj *criar(int custo, int no, ladj *g)
{
    ladj *novo = g, *aux;
    novo = (ladj *)malloc(sizeof(ladj));
    if (novo == NULL)
    {
        exit(-1);
    }
    if (g != NULL)
    {
        for (aux = g; aux->next != NULL; aux = aux->next)
            ;
        aux->next = novo;
    }
    else
    {
        novo->no = no;
        novo->next = NULL;
        novo->custo = custo;
        return novo;
    }
    novo->no = no;
    novo->next = NULL;
    novo->custo = custo;
    return g;
}

int main(int argc, char *argv[])
{
    FILE *fp, *fp2;
    char *ent, *saida;
    G *g;
    int i, custo, no1, no2;
    ladj *aux, *aux2;
    if (argc < 2)
    {
        exit(-1);
    }
    ent = (char *)malloc((strlen(argv[1]) + 1) * sizeof(char));
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
    strcat(ent, ".ladj");
    if ((fp2 = fopen(ent, "w")) == NULL)
    {

        exit(-1);
    }
    g = (G *)malloc(sizeof(G));
    if (g == NULL)
    {
        exit(-1);
    }
    fscanf(fp, "%d %d", &g->V, &g->E);
    g->table = (ladj **)calloc(1, sizeof(ladj *) * (g->V));

    for (i = 0; i < (g->E); i++)
    {
        fscanf(fp, "%d %d %d", &no1, &no2, &custo);
        g->table[no1] = criar(custo, no2, g->table[no1]);
        g->table[no2] = criar(custo, no1, g->table[no2]);
    }
    fprintf(fp2, "%d\n", g->V);
    for (i = 0; i < (g->V); i++)
    {
        for (aux = g->table[i]; aux != NULL; aux = aux->next)
        {
            fprintf(fp2, "%d:%d ", aux->no, aux->custo);
        }
        fprintf(fp2, "-1\n");
    }

    fclose(fp);
    fclose(fp2);
    free(ent);
    for (i = 0; i < (g->V); i++)
    {
        for (aux = g->table[i]; aux != NULL; aux = aux2)
        {
            aux2 = aux->next;
            free(aux);
        }
    }
    free(g->table);
    free(g);
    return 0;
}