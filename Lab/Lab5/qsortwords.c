/******************************************************************************
 * (c) 2010-2020 IST AED Team
 * Last modified: abl 2020-04-21
 *
 * NAME
 *   sortwords.c
 *
 * DESCRIPTION
 *   Main program for unique word finding and sorting with tables
 *
 * COMMENTS
 *   Code for preliminary distribution, to be completed
 ******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "word.h"

enum sort_order
{
    ascending,
    descending
};

enum sort_criteria
{
    alphabetic,
    length,
    occurrences
};

int OP_CNT = 0; /* global variable, to simplify complexity assessment */

/******************************************************************************
 * sort ()
 *
 * Arguments: a - table of items to sort
 *            l, r - limits on table to consider
 *            less - item comparison function
 * Returns: (void)
 * Side-Effects: table is sorted in place
 *
 * Description: implements "some" sorting algorithm for abstract type (Item),
 *       using also an abstract type comparison function (*less)
 *           a[] - array of abstract type Item to be sorted
 *           l - index of first element in the array to be sorted
 *           r - last element of the array to be sorted
 *           (*less)(Item,Item) - abstract type comparison function
 *****************************************************************************/
#define exch(a, b)  \
    {               \
        Item t = a; \
        a = b;      \
        b = t;      \
    }
#define eq(a, b) (!less(a, b) && !less(b, a))

void sort(Item a[], int l, int r, int (*less)(Item, Item))
{
    int i, j, k, p, q;
    Item v;
    if (r <= l)
        return;
    v = a[r];
    OP_CNT++;
    i = l - 1;
    j = r;
    p = l - 1;
    q = r;
    for (;;)
    {
        OP_CNT++;
        while (less(a[++i], v)) /*Começa no inicio e procura até encontrar um número maior ou igual a v*/
        {
            OP_CNT++;
        }
        OP_CNT++;
        while (less(v, a[--j])) /*Começa no final -1 e procura até encontrar um número menor ou igual a v*/
        {
            OP_CNT++;
            if (j == l) /*Caso em que não encontra nenhum menor ou igual a v*/
                break;
        }
        if (i >= j) /*Se já tiver o maior à direita e o menor à esquerda sai do for(;;)*/
            break;
        exch((a[i]), (a[j]));
        OP_CNT += 4;
        if (eq(a[i], v))
        {
            p++;
            exch((a[p]), (a[i])); /*Mete o a[i] no canto esquerdo*/
            OP_CNT += 2;
        }
        OP_CNT += 2;
        if (eq(a[j], v))
        {
            q--;
            exch((a[q]), (a[j])); /*Mete o a[j] no canto direito*/
            OP_CNT += 2;
        }
    }
    exch((a[i]), (a[r])); /*Meter o pivot no sitio certo da lista, onde tudo à esquerda é menor e tudo à direita é maior*/
    OP_CNT += 2;
    j = i - 1;
    i = i + 1;
    for (k = l; k <= p; k++, j--) /*traz os do canto esquerdo para o lado esquerdo do pivot, visto que era o mesmo número a posição deles tem de ser ali*/
        exch((a[k]), (a[j]));
    OP_CNT += 2;
    for (k = r - 1; k >= q; k--, i++) /*traz os do canto direito para o lado direito do pivot, visto que era o mesmo número a posição deles tem de ser ali*/
        exch((a[k]), (a[i]));
    OP_CNT += 2;
    sort(a, l, j, less); /*volta a chamar as funções do inicio até ao número anterior metido por ultimo na esquerda naquela troca de cima*/
    sort(a, i, r, less); /*volta a chamar as funções desde do número a seguir ao metido por ultimo na direita naquela troca de cima, até ao fim*/
}

/******************************************************************************
 * main ()
 *
 *****************************************************************************/

int main(int argc, char **argv)
{
    int TnumWords;   /* total number of words in input file */
    int numWords;    /* number of distint words in input file */
    Tabword tabword; /* table holding the structure */

    /* default initialization for alfabetic order and ascending */
    enum sort_criteria criterio = alphabetic;
    enum sort_order sentido = ascending;
    char *file = argv[1];

    argv++; /* get past prog and file names */
    while (*(++argv))
    {
        if (strcmp(*argv, "-alfabetica") == 0)
            criterio = alphabetic;
        else if (strcmp(*argv, "-ocorrencias") == 0)
            criterio = occurrences;
        else if (strcmp(*argv, "-comprimento") == 0)
            criterio = length;
        else if (strcmp(*argv, "-a") == 0)
            sentido = ascending;
        else if (strcmp(*argv, "-d") == 0)
            sentido = descending;
        else
        {
            fprintf(stderr, "Wrong arguments\n");
            exit(3);
        }
    }
    TnumWords = AllocWordArray(&tabword, file);
    printf("Total number of words: %d\n", TnumWords);

    numWords = FillInWordArray(tabword, file);
    printf("Number of different words = %d\n", numWords);

    OP_CNT = 0;

    /*  Call the sorting function using as argument the
        appropriate comparison function selected by user option */
    if ((criterio == alphabetic) && (sentido == ascending))
    {
        sort((Item *)tabword, 0, numWords - 1, &LessAlphabetic);
    }
    else if (((criterio == alphabetic) && (sentido == descending)))
    {
        sort((Item *)tabword, 0, numWords - 1, &MaisAlphabetic);
    }
    else if ((criterio == occurrences) && (sentido == ascending))
    {
        sort((Item *)tabword, 0, numWords - 1, &Lessoccurrence);
    }
    else if (((criterio == occurrences) && (sentido == descending)))
    {
        sort((Item *)tabword, 0, numWords - 1, &Maisoccurrence);
    }
    else if ((criterio == length) && (sentido == ascending))
    {
        sort((Item *)tabword, 0, numWords - 1, &Lesslength);
    }
    else if (((criterio == length) && (sentido == descending)))
    {
        sort((Item *)tabword, 0, numWords - 1, &Maislength);
    }

    /* other user options */
    /*==== TODO ====*/

    /* ---------------------------------------- */
    printf("%d\n", numWords);

    WriteFile(tabword, file, numWords);
    /*  printf("Number of different words: %d\n", n_palavras);  */

    /* -- Insert code to call functions to free allocated memory -- */

    /*==== TODO ====*/

    /* ------------------------------------------------------------ */
    FreeWordArray(&tabword, numWords);

    return 0;
}
