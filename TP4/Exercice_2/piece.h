#pragma once

#include <stdbool.h>

typedef struct piece piece_t, *piece_p;


//Constructeur de la structure piece_t.
piece_p piece_init(int lng, int lrg, int nb_f, bool chauffage, char* __nom);

//Renvoie une piece generee aleatoirement.
piece_p piece_init_aleatoire();

//Alloue un tableau de length elements de type piece_p.
piece_p* piece_init_array(int length);


//Destructeur de la structure piece_t.
void piece_free(piece_p this);

//Pour free un tableau de piece_p.
void piece_free_array(piece_p* this);


//Affiche dans stdout tous les attributs d'une piece.
void piece_affiche(piece_p piece);


//Renvoie la surface d'une piece.
int piece_get_surface(piece_p p);

//Renvoie le nombre de fenetres d'une piece.
int piece_get_nb_fenetres(piece_p p);

//Renvoie true si p est chauffee, false sinon.
bool piece_possede_chauffage(piece_p p);