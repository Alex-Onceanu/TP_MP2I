#pragma once

#include "maison.h"

typedef struct quartier quartier_t, *quartier_p;


//Constructeur de la structure quartier_t.
quartier_p quartier_init(maison_p __maisons[], int __nb_maisons, int __prix);

//Renvoie un quartier genere aleatoirement.
quartier_p quartier_init_aleatoire();

//Alloue un tableau de length elements de type quartier_p.
quartier_p* quartier_init_array(int length);


//Destructeur de la structure quartier_t
void quartier_free(quartier_p);

//Pour free un tableau de quartiers.
void quartier_free_array(quartier_p*);


//Accesseur de l'attribut prix_moyen_m2
int quartier_get_prix_moyen(quartier_p q);

//Renvoie le cout total des maisons d'un quartier.
int quartier_cout_total(quartier_p q);

//Affiche toutes les maisons d'un quartier.
void quartier_affiche(quartier_p q);