#pragma once

#include <stdio.h>

#include "choix.h"

typedef struct page page_t, *page_p;

//Lit une page dans un fichier f (constructeur).
page_p generer_page(FILE* f);

//Alloue un tableau de length elements de type page_p
page_p* page_init_array(int length);


//Affiche le texte d'une page, puis ses choix.
//Renvoie le numero de la prochaine page a lire, choisie par l'utilisateur.
int page_afficher(page_p this);


//Accesseur de l'attribut texte.
char* page_get_texte(page_p this);

//Accesseur de l'attribut n_choix.
int page_get_n_choix(page_p this);

//Accesseur de l'attribut choix.
choix_p* page_get_choix(page_p this);


//Destructeur de la structure page_t.
void free_page(page_p this);