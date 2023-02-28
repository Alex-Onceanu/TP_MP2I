#include <stdio.h>
#include <assert.h>


void somme_produit_max(int a, int b, int* somme, int* produit, int* max)
{
    //Les variables pointées par produit, somme, max contiendront respectivement :
    // a + b, a * b, maximum(a, b)
    assert(somme != NULL && produit != NULL && max != NULL);
    *somme = a + b;
    *produit = a * b;
    *max = a >= b ? a : b;
}


int main()
{
    int a = 3, b = 4;
    int som = 0;
    int prod = 0;
    int mx = 0;

    somme_produit_max(a, b, &som, &prod, &mx);
    printf("%d %d %d %d %d\n", a, b, som, prod, mx);

    return 0;
}