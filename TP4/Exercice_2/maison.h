#pragma once

#include "etage.h"

typedef struct maison maison_t, *maison_p;


//Constructeur de la structure maison_t
maison_p maison_init(etage_p __etages[], int __nb_etages);

//Renvoie une maison generee aleatoirement.
maison_p maison_init_aleatoire();

//Alloue un tableau de length elements de type maison_p
maison_p* maison_init_array(int length);


//Destructeur de la structure maison_t.
void maison_free(maison_p this);

//Pour free un tableau de maisons.
void maison_free_array(maison_p* this);


//Affiche les attributs de chaque etage de la maison.
void maison_affiche(maison_p maison);

//Renvoie une nouvelle maison (NULL si m1 et m2 sont NULL).
//m1 est empilee sur m2.    
maison_p maison_empiler(maison_p m1, maison_p m2);


//Renvoie le nombre de fenetres d'une maison.
int maison_get_nb_fenetres(maison_p m);

//Renvoie la surface totale d'une maison.
int maison_get_surface(maison_p m);

//Renvoie le nombre de pieces chauffees d'une maison.
int maison_get_nb_chauffages(maison_p m);
