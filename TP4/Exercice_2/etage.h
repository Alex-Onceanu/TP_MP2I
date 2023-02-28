#pragma once

#include "piece.h"

typedef struct etage etage_t, *etage_p;


//Constructeur de la structure etage_t.
etage_p etage_init(piece_p __pieces[], int __nb_pieces);

//Renvoie un etage genere aleatoirement.
etage_p etage_init_aleatoire();

//Alloue un tableau de length elements de type etage_p.
etage_p* etage_init_array(int length);


//Destructeur de la structure etage_t.
void etage_free(etage_p this);
//Pour free un tableau de etage_p.
void etage_free_array(etage_p* this);


//Affiche les informations de chaque piece d'un etage.
void etage_affiche(etage_p etage);


//Renvoie le nombre de fenetres dans un etage.
int etage_get_nb_fenetres(etage_p e);

//Renvoie la surface totale d'un etage.
int etage_get_surface(etage_p e);

//Renvoie le nombre de pieces chauffees d'un etage.
int etage_get_nb_chauffages(etage_p e);