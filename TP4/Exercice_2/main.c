#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "piece.h"
#include "etage.h"
#include "maison.h"
#include "ville.h"

int main()
{
    srand(time(NULL));

    //Instanciation d'une maison grâce aux constructeurs
    piece_p p1 = piece_init(3, 9, 2, true, "Premiere piece !!!");
    piece_p p2 = piece_init(5, 5, 3, true, "Chambre a dormir");
    piece_p p3 = piece_init(4, 6, 2, false, "Chambre a manger");
    piece_p p4 = piece_init(1, 2, 0, false, "la cave");

    piece_p pieces1[3] = { p1,p2,p3 };
    piece_p pieces2[2] = { p3,p4 };

    etage_p e1 = etage_init(pieces1, 3);
    etage_p e2 = etage_init(pieces2, 2);

    etage_p etages1[2] = { e1,e2 };
    maison_p m1 = maison_init(etages1, 2);

    maison_affiche(m1);
    printf("%d fenetres !\n", maison_get_nb_fenetres(m1));
    printf("Surface de %d m**2.\n", maison_get_surface(m1));
    printf("%d pieces sont chauffees.\n", maison_get_nb_chauffages(m1));
    
    
    maison_p m2 = maison_init_aleatoire();
    printf("\nEmpilemennnnnt....\n");

    maison_p empilage = maison_empiler(m1, m2);
    maison_affiche(empilage);

    printf("_______________________Creation de ville...___________________\n\n");

    ville_p v1 = ville_init_aleatoire();

    // /!\ la fonction ville_affiche prend BEAUCOUP de place dans le terminal.
    //ville_affiche(v1);
    ville_affiche_prix_moyen(v1);
    printf("\nCout total de la ville : %d$\n", ville_cout_total(v1));

    maison_free(empilage);
    free(m1);
    free(m2);

    ville_free(v1);

    return 0;
}