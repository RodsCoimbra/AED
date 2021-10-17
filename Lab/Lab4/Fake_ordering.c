/*#define swap(a, b)
{
    int t;
    t = a;
    a = b;
    b = t;
}

void fake ordering(int *vec, int iL, int iR)
{
    int tmp;
    int iM = (iR - iL) / 2;     //1 
    if (vec[iL] > vec[iM])      //2 acessos e 1 comparação = 3
        swap(vec[iL], vec[iM]); //5
    if (vec[iM] > vec[iR])      //3
        swap(vec[iM], vec[iR]); //5
    if (vec[iL] > vec[iM])      //3
        swap(vec[iL], vec[iM]);  //5   
    fake ordering(vec, iL, iM);     repete infinitamente?????????
    fake ordering(vec, iM + 1, iR); ??????????
    return;
}*/