#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "grid.h"
#include "chemins.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Mauvaise utilisation du programme, preciser le fichier d'entree en argument.\n");
        return -1;
    }
    srand(time(NULL));

    GRID *g = lire_grille(argv[1]);
    GRID_print(g);

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

    int **progdyn = dechets_progdyn(g);
    for (int y = 0; y < height(g); ++y)
    {
        for (int x = 0; x < width(g); ++x)
        {
            printf("%5d", progdyn[y][x]);
        }
        printf("\n");
    }
    // On a le tableau de progdyn qui donne la solution optimale
    // Reste a reconstruire le chemin a partir du tableau

    GRID_free(g);

    return 0;
}