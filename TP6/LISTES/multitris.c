/*
J'ai inclus ce programme dans ce rendu, même s'il se rapporte davantage
à la partie "compétences numériques" que j'enverrai demain en pdf.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "liste.h"
#include "tri_rapide.h"
#include "tri_insertion.h"

int main(int argc, char** argv)
{
    if(argc != 4)
    {
        printf("Mauvaise utilisation du programme. Format : \"./a.out <n> <k> <ALGO>\"\n\
            Avec n entier taille de la liste a trier, k nombre (entier) de repetitions du tri,\
            ALGO pouvant etre \"RAPIDE\" ou \"INSERTION\" nom de l'algorithme a utiliser.\n");
    }

    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    char* algo = malloc(sizeof(char) * 10);
    strcpy(algo, argv[3]);

    LISTE* l;
    LISTE* trie;

    if(strcmp(algo, "RAPIDE") == 0)
    {
        for(int i = 0; i < k; ++i)
        {
            l = aleatoire(n);
            trie = tri_rapide(l);

            free_liste(l);
            free_liste(trie);
        }
    }
    else if(strcmp(algo, "INSERTION") == 0)
    {
        for(int i = 0; i < k; ++i)
        {
            l = aleatoire(n);
            trie = tri_insertion(l);

            free_liste(l);
            free_liste(trie);
        }
    }
    else
    {
        printf("Algo inconnu. On trie uniquement avec \"INSERTION\" ou \"RAPIDE\".\n");
    }

    free(algo);

    printf("Done.\n");

    return 0;
}