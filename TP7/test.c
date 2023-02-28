#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "hashtable.h"
#include "element.h"


int main()
{
    /*TEST hash*/
    assert(hash("bonjour", 101) == 53);
    assert(hash("voici un texte a hacher", 503) == 488);
    assert(hash("voici un texte a macher", 503) == 236);
    
    printf("hash test passed.\n");

    /*TEST egal*/
    assert(egal("Hello world !", "Hello world !"));
    assert(egal("Arrete de me copier", "Arrete de me copier"));
    
    printf("egal test passed.\n");
    
    /*TEST chaine*/
    CHAINE* t = chaine_vide();
    assert(tete(t) == NULL);
    assert(taille(t) == 0);
    assert(recherche_chaine(t, "Existence") == NULL);

    ajouter_debut(t, "2 2 +", 4);
    assert(suivant(tete(t)) == NULL);
    ajouter_debut(t, " ", 0);

    ajouter_debut(t, "4 7 8 * +", 60);
    ajouter_debut(t, "pi 2 -1 sqrt * * exp", 1);
    assert(recherche_chaine(t, "2 2 +")->val == 4);
    VAL v = tete(t)->val;
    supprimer_chaine(t, tete(t));
    assert(tete(t)->val != v);
    assert(taille(t) == 3);
    //print_chaine(t);
    free_chaine(t);

    printf("chaine test passed.\n");

    /*TEST dict*/
    const int TAILLE = 10;
    DICT* d = dict_vide(TAILLE);
    inserer(d, "2 2 +", 4);

    assert(rechercher(d, "2 2 +") == 4);
    
    inserer(d, "4 7 8 * +", 60);
    inserer(d, "pi 2 -1 sqrt * * exp", 1);

    assert(rechercher(d, "2 2 +") == 4);
    assert(rechercher(d, "pi 2 -1 sqrt * * exp") == 1);
    assert(appartient(d, "4 7 8 * +"));

    supprimer(d, "4 7 8 * +");
    inserer(d, "4 7 8 * +", 61);
    inserer(d, "3 8 8 * +", 67);

    assert(rechercher(d, "4 7 8 * +") == 61);
    assert(rechercher(d, "3 8 8 * +") == 67);

    debug_dict(d);

    free_dict(d);

    printf("dict test passed.\n");

    return 0;
}