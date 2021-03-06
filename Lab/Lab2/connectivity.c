/******************************************************************************
 * (c) 2010-2019 AED Team
 * Last modified: abl 2019-02-22
 *
 * NAME
 *   connectivity.c
 *
 * DESCRIPTION
 *   Algorithms for solving the connectivity problem -  QF QU WQU CWQU
 *   For each method count number of entry pairs and the number of links
 *
 * COMMENTS
 *   Code for public distribution
 ******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include "connectivity.h"

#define DEBUG 0

/******************************************************************************
 * quick_find()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Quick Find algorithm
 *****************************************************************************/

void quick_find(int *id, int N, FILE * fp, int quietOut)
{
   int i, p, q, t;
   int pairs_cnt = 0;            /* connection pairs counter */
   int links_cnt = 0;            /* number of links counter */
   int conjuntos = 0;
   unsigned long int find = 0;
   unsigned long int uni = 0;
   /* initialize; all disconnected */
   for (i = 0; i < N; i++) {
      id[i] = i;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2) {
      pairs_cnt++;
      find+=2;
      /* do search first */
      if (id[p] == id[q]) {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }
      

      /* pair has new info; must perform union */
      uni++;
      for (t = id[p], i = 0; i < N; i++, uni++) {
         if (id[i] == t) {
            id[i] = id[q];
            uni+=2;
         }
      }
      links_cnt++;
      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("QF: The number of links performed is %d for %d input pair.\t Find - %lu, Union - %lu Total - %lu.\n\n\n",
          links_cnt, pairs_cnt, find, uni, find+uni);

   int numeros[N], flag,j, aux = 0;
   for(int i = 0; i < N; i++){
      numeros[i] = -1;
   }

   for(i=0;i < N; i++){
      for(j=0, flag = 1;numeros[j]!= -1;j++){
         if(numeros[j] == id[i]){
            flag = 0;
            break;
         }
      }
      if(flag){
         conjuntos++;
         numeros[j] = id[i];
      }
   }
   for(i=0;numeros[i]!= -1 && i < N; i++){
      for(j=aux, flag = 0; j < N; j++){
         if(id[j] == numeros[i]){
            if (flag){
               printf("-");
            }
            else{ 
               flag = 1;
               aux = j;
            }
            printf("%d", j);
         }
      }
      printf("\n");
   }
   printf("N??mero de conjuntos: %d\t", conjuntos);
   return;
}


/******************************************************************************
 * quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Quick Union algorithm
 *****************************************************************************/

void quick_union(int *id, int N, FILE * fp, int quietOut)
{

   int i, j, p, q;
   int pairs_cnt = 0;            /* connection pairs counter */
   int links_cnt = 0;            /* number of links counter */
   unsigned long int find = 0;
   unsigned long int uni = 0;
   /* initialize; all disconnected */
   for (i = 0; i < N; i++) {
      id[i] = i;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2) {
      pairs_cnt++;
      i = p;
      j = q;
      find+=2;
      /* do search first */
      while (i != id[i]) {
         i = id[i];
         find+=2;
      }
      while (j != id[j]) {
         j = id[j];
         find+=2;
      }
      if (i == j) {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union */
      id[i] = j;
      links_cnt++;
      uni++;
      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("QU: The number of links performed is %d for %d input pairs.\t Find - %lu, Union - %lu Total - %lu.\n\n\n",
          links_cnt, pairs_cnt, find, uni, find+uni);
}


/******************************************************************************
 * weighted_quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Weighted Quick Union algorithm
 *****************************************************************************/

void weighted_quick_union(int *id, int N, FILE * fp, int quietOut)
{

   int i, j, p, q;
   int *sz = (int *) malloc(N * sizeof(int));
   int pairs_cnt = 0;            /* connection pairs counter */
   int links_cnt = 0;            /* number of links counter */
   unsigned long int find = 0;
   unsigned long int uni = 0;
   /* initialize; all disconnected */
   for (i = 0; i < N; i++) {
      id[i] = i;
      sz[i] = 1;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2){
      pairs_cnt++;
      /* do search first */
      for (i = p; i != id[i]; i = id[i], find+=2);
      for (j = q; j != id[j]; j = id[j], find+=2);
      find+=2;
      if (i == j) {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union; pick right direction */
      if (sz[i] < sz[j]) {
         id[i] = j;
         sz[j] += sz[i];
         uni+=6;
      }
      else {
         id[j] = i;
         sz[i] += sz[j];
         uni+=6;
      }
      links_cnt++;

      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("WQU: The number of links performed is %d for %d input pairs.\t Find - %lu, Union - %lu Total - %lu.\n\n\n",
          links_cnt, pairs_cnt, find, uni, find+uni);
}


/******************************************************************************
 * compressed_weighted_quick_union()
 *
 * Arguments: id - array with connectivity information
 *            N - size of array
 *            fp - file pointer to read data from
 *            quietOut - to reduce output to just final count
 * Returns: (void)
 * Side-Effects: pairs of elements are read and the connectivity array is
 *               modified
 *
 * Description: Compressed Weighted Quick Union algorithm
 *****************************************************************************/

void compressed_weighted_quick_union(int *id, int N, FILE * fp, int quietOut)
{
   int i, j, p, q, t, x;
   int *sz = (int *) malloc(N * sizeof(int));
   int pairs_cnt = 0;            /* connection pairs counter */
   int links_cnt = 0;            /* number of links counter */
   unsigned long int find = 0;
   unsigned long int uni = 0;
   unsigned long int comp = 0;
   /* initialize; all disconnected */
   for (i = 0; i < N; i++) {
      id[i] = i;
      sz[i] = 1;
   }

   /* read while there is data */
   while (fscanf(fp, "%d %d", &p, &q) == 2) {
      pairs_cnt++;

      /* do search first */
      for (i = p; i != id[i]; i = id[i], find+=2);
      for (j = q; j != id[j]; j = id[j], find+=2);
      find+=2;
      if (i == j) {
         /* already in the same set; discard */
#if (DEBUG == 1)
         printf("\t%d %d\n", p, q);
#endif
         continue;
      }

      /* pair has new info; must perform union; pick right direction */
      if (sz[i] < sz[j]) {
         id[i] = j;
         sz[j] += sz[i];
         uni+=6;
         t = j;
      }
      else {
         id[j] = i;
         sz[i] += sz[j];
         uni+=6;
         t = i;
      }
      links_cnt++;
      /* retrace the path and compress to the top */
      for (i = p; i != id[i]; i = x, comp+=3) {
         x = id[i];
         id[i] = t;
      }
      comp++;
      for (j = q; j != id[j]; j = x, comp+=3) {
         x = id[j];
         id[j] = t;
      }
      comp++;
      if (!quietOut)
         printf(" %d %d\n", p, q);
   }
   printf("CWQU: The number of links performed is %d for %d input pair.\t Find - %lu, Union - %lu, Total - %lu.\n\n\n",
          links_cnt, pairs_cnt, find, uni, find+uni+comp);

   return;
}
