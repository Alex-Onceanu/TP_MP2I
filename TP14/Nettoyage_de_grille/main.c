#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "grid.h"
#include "chemins.h"

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Mauvaise utilisation du programme, preciser le fichier d'entree en argument, ainsi que k (contenance du sac).\n");
        return -1;
    }
    srand(time(NULL));

    GRID *g = lire_grille(argv[1]);
    // GRID_print(g);

    printf("3 chemins aléatoires :\n");
    const int nb_essais = 3;
    char *chemin;
    for (int i = 0; i < nb_essais; ++i)
    {
        chemin = chemin_aleatoire(g);
        printf("Chemin : %s\nValeur : %d\n\n", chemin, valeur(g, chemin));
        free(chemin);
    }

    chemin = chemin_glouton(g);
    printf("Glouton : %s\nValeur : %d\n\n", chemin, valeur(g, chemin));
    free(chemin);

    // 8) Valeurs gloutonnes pour les 3 exemples : 101, 1069, 21970
    // 9) Contrexemple : chemin DDDRRRR dans le 4x5

    // int **progdyn = dechets_progdyn(g);
    int **progdyn = dechets_progdyn(g);
    // On a le tableau de progdyn qui donne la solution optimale
    // for (int y = 0; y < height(g); ++y)
    // {
    //     for (int x = 0; x < width(g); ++x)
    //     {
    //         printf("%5d", progdyn[y][x]);
    //     }
    //     printf("\n");
    // }

    // Reste a reconstruire le chemin a partir du tableau
    char *chemin_progdyn = reconstruction(progdyn, g);
    printf("Chemin prog dyn : %s\nValeur : %d\n", chemin_progdyn, valeur(g, chemin));
    free(chemin_progdyn);

    // Partie Bonus : on prend un sac de taille k
    // Où k est donné en argv
    int k = atoi(argv[2]);
    int **progdyn_contrainte = dechets_contrainte_progdyn(g, k);

    for (int y = 0; y < height(g); ++y)
    {
        for (int x = 0; x < width(g); ++x)
        {
            printf("%5d", progdyn_contrainte[y][x]);
        }
        printf("\n");
    }

    char *chemin_bonus = reconstruction_contrainte(progdyn_contrainte, g, k);
    int val = trouver_max(progdyn_contrainte, width(g), height(g), k, NULL, NULL);
    printf("Chemin avec un sac de taille %d : %s\nValeur : %d\n", k, chemin_bonus, val);
    free(chemin_bonus);

    GRID_free(g);

    return 0;
}