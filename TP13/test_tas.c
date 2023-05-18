#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <assert.h>

#include "tas.h"

bool est_tas(int *t, int n)
{
    int i = 0;
    bool a, b;
    while (i < n)
    {
        if (gauche(i) < n)
        {
            a = t[i] < t[gauche(i)];
        }
        else
            a = true;
        if (droite(i) < n)
        {
            b = t[i] < t[droite(i)];
        }
        else
            b = true;

        if (!a || !b)
            return false;

        i++;
    }
    return true;
}

int randint(int a, int b)
{
    return (rand() % (b - a)) + a;
}

int *tableau_aleatoire(int n, int a, int b)
{
    int *res = malloc(n * sizeof(int));

    for (int i = 0; i < n; ++i)
    {
        res[i] = randint(a, b);
    }

    return res;
}

bool est_trie(int *t, int n)
{
    if (n == 0)
        return true;
    for (int i = 1; i < n; ++i)
    {
        if (t[i] < t[i - 1])
            return false;
    }
    return true;
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    const int n = 4;
    HEAP *h = tas_vide(n);

    assert(h != NULL);
    printf("ASSERT 1 OK\n");
    int *t = tableau_aleatoire(n - 1, 0, 8);
    for (int i = 0; i < n; ++i)
    {
        ajouter(h, t[i]);
    }
    ajouter(h, 9);
    assert(extraire_max(h) == 9);
    printf("ASSERT 2 OK\n");

    int laid[4] = {3, 2, 0, 1};
    tri_par_tas(laid, 4);

    assert(est_trie(laid, 4));
    printf("ASSERT 3 OK\n");

    return 0;
}