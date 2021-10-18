/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define swap(a, b) \
    {              \
        int t;     \
        t = a;     \
        a = b;     \
        b = t;     \
    }

void fakeordering(int *vec, int iL, int iR)
{
    int tmp;
    int iM = (iR - iL) / 2;        //1
    if (vec[iL] > vec[iM])         //2 acessos e 1 comparação = 3
        swap(vec[iL], vec[iM]);    //5
    if (vec[iM] > vec[iR])         //3
        swap(vec[iM], vec[iR]);    //5
    if (vec[iL] > vec[iM])         //3
        swap(vec[iL], vec[iM]);    //5
    fakeordering(vec, iL, iM);     //repete infinitamente?????????
    fakeordering(vec, iM + 1, iR); //??????????
    return;
}

int main()
{
    int vec[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    fakeordering(vec, 1, 7);
    return 0;
}*/