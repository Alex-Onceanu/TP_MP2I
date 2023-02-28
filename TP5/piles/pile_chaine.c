#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "pile.h"

typedef struct maillon{
    T elem;
    struct maillon* suivant;
}MAILLON;

struct pile_{
    MAILLON* sommet;
};

void affiche_element(T x)
{
    printf("%c", x);
}

void affiche_pile(PILE* p)
{
    if(p == NULL) return;
    MAILLON* curseur = p->sommet;

    while(curseur != NULL)
    {
        affiche_element(curseur->elem);
        printf("\n");
        curseur = curseur->suivant;
    }
}

PILE* pile_vide()
{
    PILE* resultat = malloc(sizeof(PILE));
    resultat->sommet = NULL;
    return resultat;
}

bool est_vide(PILE* p)
{
    if(p == NULL) return true;
    return p->sommet == NULL;
}

void empiler(PILE* p, T x)
{
    assert(p != NULL);
    MAILLON* nouv = malloc(sizeof(MAILLON));
    nouv->elem = x;
    nouv->suivant = p->sommet;
    p->sommet = nouv;
}

T depiler(PILE* p)
{
    assert(p != NULL && p->sommet != NULL);
    MAILLON* ancien_sommet = p->sommet;
    p->sommet = p->sommet->suivant;
    T resultat = ancien_sommet->elem;

    free(ancien_sommet);

    return resultat;
}

void free_pile(PILE* p)
{
    assert(p != NULL);
    MAILLON* curseur = p->sommet;
    MAILLON* ancien;

    while(curseur != NULL)
    {
        ancien = curseur;
        curseur = curseur->suivant;
        free(ancien);
    }

    free(p);
}