#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "liste.h"
#include "tri_rapide.h"
#include "tri_insertion.h"


//tests pour la creation de liste et toute la partie d'avant les tris
#if 0

int main()
{
    LISTE* l1 = creer_liste();
    LISTE* l2 = creer_liste();
    // LISTE* l3 = creer_liste();
    // LISTE* m1 = creer_liste();
    // LISTE* m2 = creer_liste();

    ajouter(l1, 31);
    ajouter(l2, 31);
    //ajouter(l3, 75);

    printf("Tests en place :\n");

    inserer(l1, tete(l1), 70);
    ajouter(l1, 38);
    
    PLACE* laplace = tete(l1);
    laplace = suivant(laplace);
    modifier(laplace, 31830);
    modifier(precedent(laplace), 70207);

    supprimer(l1, queue(l1));

    affiche_liste(l1);
    printf("De taille %d\n", taille(l1));

    printf("Et l'autre liste :\n");
    affiche_liste(l2);
    printf("La tete vaut %d, et la queue vaut %d\n", contenu(tete(l2)), contenu(queue(l2)));
    supprimer(l2, tete(l2));
    printf("Une liste vide ressemble à : ");
    affiche_liste(l2);

    free_liste(l1);
    free_liste(l2);

    return 0;
}

#else

int main()
{
    srand(time(NULL));
    const int N = 10;
    LISTE* l1 = aleatoire(N);
    
    affiche_liste(l1);
    printf("On trie...\n");
    LISTE* trie = tri_rapide(l1);
    affiche_liste(trie);
    LISTE* trie2 = tri_insertion(l1);
    affiche_liste(trie2);

    assert(est_triee(trie));
    assert(est_triee(trie2));

    free_liste(l1);
    free_liste(trie);
    free_liste(trie2);

    return 0;
}

#endif