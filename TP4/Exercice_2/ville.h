#pragma once

#include "quartier.h"

typedef struct ville ville_t, *ville_p;


//Constructeur de la structure ville_t.
ville_p ville_init(quartier_p** __quartiers, int __nb_lignes, int __nb_colonnes);

//Renvoie une ville generee aleatoirement.
ville_p ville_init_aleatoire();

//Alloue un tableau de length elements de type ville_p.
ville_p* ville_init_array(int length);


//Destructeur de la structure ville_t
void ville_free(ville_p);

//Pour free un tableau de villes.
void ville_free_array(ville_p*);

//Renvoie le cout total des maisons d'une ville.
int ville_cout_total(ville_p v);

//Affiche la matrice des quartiers numerotes d'une ville.
//Et leur prix moyen de m2.
void ville_affiche_prix_moyen(ville_p v);

//Affiche tous les quartiers d'une ville
void ville_affiche(ville_p v);