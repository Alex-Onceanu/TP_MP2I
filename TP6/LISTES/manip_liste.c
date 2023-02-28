#include <stdio.h>
#include <stdlib.h>

#include "liste.h"

PLACE* recherche(LISTE* l, int x)
{
    PLACE* curs = tete(l);
    for(int i = 0; i < l->taille; ++i)
    {
        if(contenu(curs) == x)
        {
            return curs;
        }
        curs = suivant(curs);
    }
    return NULL;
}

void supprimer_occs(LISTE* l, int x)
{
    PLACE* curs = tete(l);
    PLACE* tmp;
    for(int i = 0; i < l->taille; ++i)
    {
        tmp = curs;
        curs = suivant(curs);
        if(contenu(tmp) == x)
        {
            supprimer(l, tmp);
        }
    }
}