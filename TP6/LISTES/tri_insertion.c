#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "liste.h"

LISTE* aleatoire2(int n)
{
    LISTE* resultat = creer_liste();
    for(int i = 0; i < n; ++i)
    {
        ajouter(resultat, rand() % 101);
    }
    return resultat;
}


bool est_triee2(LISTE* l)
{
    PLACE* curs = tete(l);
    PLACE* prc = curs;
    for(int i = 0; i < taille(l) - 1; ++i)
    {
        curs = suivant(curs);
        if(contenu(prc) > contenu(curs)) return false;
        prc = curs;
    }
    return true;
}

void insertion_triee(LISTE* l, int x)
{
    PLACE* curs = tete(l);
    for(int i = 0; i < taille(l); ++i)
    {
        if(contenu(curs) > x)
        {
            return inserer(l, curs, x);
        }
        curs = suivant(curs);
    }
    ajouter(l, x);
}

LISTE* tri_insertion(LISTE* l)
{
    LISTE* resultat = creer_liste();
    PLACE* curs = tete(l);
    for(int i = 0; i < taille(l); ++i)
    {
        insertion_triee(resultat, contenu(curs));
        curs = suivant(curs);
    }
    return resultat;
}