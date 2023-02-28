#pragma once

#include "page.h"

typedef struct livre livre_t, *livre_p;

//Ouvre un fichier "filename" et y lit un livre.
livre_p generer_livre(char* filename);


//Lance le jeu du "livre dont vous etes le heros".
//L'utilisateur va de page en page selon ses choix,
//pour obtenir diverses fins selon son parcours.
void LDVELH(livre_p bouquin);


//Accesseur de l'attribut n_pages.
int livre_get_n_pages(livre_p this);

//Accesseur de l'attribut pages.
page_p* livre_get_pages(livre_p this);


//Destructeur de la structure livre_t.
void free_livre(livre_p this);