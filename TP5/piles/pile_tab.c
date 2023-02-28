#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "pile.h"


#define Nmax 10000
struct pile_{
    int nb_elem;
    T* tab;
};

void affiche_element(T x)
{
    printf("%c", x);
}

PILE* pile_vide()
{
    PILE* resultat = malloc(sizeof(PILE));
    resultat->nb_elem = 0;
    resultat->tab = malloc(sizeof(T) * Nmax);

    return resultat;
}

bool est_vide(PILE* p)
{
    if(p == NULL) return true;
    return p->nb_elem == 0;
}

void empiler(PILE* p, T x)
{
    assert(p != NULL && p->nb_elem < Nmax);
    p->tab[p->nb_elem++] = x;
}

T depiler(PILE* p)
{
    assert(p != NULL && p->nb_elem > 0);
    return p->tab[--p->nb_elem];
}

void free_pile(PILE* p)
{
    if(p == NULL) return;
    free(p->tab);
    free(p);
}

void affiche_pile(PILE* p)
{
    if(p == NULL) return;
    for(int i = p->nb_elem - 1; i >= 0; --i)
    {
        affiche_element(p->tab[i]);
        printf("\n");
    }
}