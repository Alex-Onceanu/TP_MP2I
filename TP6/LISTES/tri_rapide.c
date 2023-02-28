#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "liste.h"


LISTE* concatenation(LISTE** ls, int n)
{
    assert(ls != NULL);
    LISTE* resultat = creer_liste();
    PLACE* curs;
    for(int i = 0; i < n; ++i)
    {
        //Pour chaque liste, on itere
        if(est_vide(ls[i])) continue;
        curs = tete(ls[i]);
        for(int j = 0; j < taille(ls[i]); ++j)
        {
            //Pour chaque elem de chaque liste, on l'ajoute au resultat
            ajouter(resultat, contenu(curs));
            curs = suivant(curs);
        }
    }
    return resultat;
}

LISTE** separer(LISTE* l, int x)
{
    LISTE** resultat = malloc(3 * sizeof(LISTE*));
    //LISTE** resultat = malloc(sizeof(LISTE*));
    
    //liste_plus_petits, liste_egaux, liste_plus_grands
    LISTE* lpp = creer_liste();
    LISTE* leq = creer_liste();
    LISTE* lpg = creer_liste();

    PLACE* curs = tete(l);
    int elem;
    for(int i = 0; i < taille(l); ++i)
    {
        elem = contenu(curs);
        if(elem < x)
        {
            ajouter(lpp, elem);
        }
        else if(elem > x)
        {
            ajouter(lpg, elem);
        }
        else
        {
            ajouter(leq, elem);
        }
        curs = suivant(curs);
    }

    resultat[0] = lpp;
    resultat[1] = leq;
    resultat[2] = lpg;

    assert(taille(lpp) + taille(leq) + taille(lpg) == taille(l));

    return resultat;
}


LISTE* aleatoire(int n)
{
    LISTE* resultat = creer_liste();
    for(int i = 0; i < n; ++i)
    {
        ajouter(resultat, rand() % 101);
    }
    return resultat;
}


bool est_triee(LISTE* l)
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

LISTE* tri_rapide(LISTE* l)
{
    assert(l != NULL);
    if(!est_vide(l))
    {
        PLACE* x = tete(l);
        LISTE** sep = separer(l, contenu(x));

        LISTE* lpp_triee = tri_rapide(sep[0]);
        LISTE* lpg_triee = tri_rapide(sep[2]);
        free_liste(sep[0]);
        free_liste(sep[2]);
        sep[0] = lpp_triee;
        sep[2] = lpg_triee;

        LISTE* res = concatenation(sep, 3);
        
        for(int i = 0; i < 3; ++i)
        {
            free_liste(sep[i]);
        }
        free(sep);

        return res;
    }
    else
    {
        return creer_liste();
    }
}