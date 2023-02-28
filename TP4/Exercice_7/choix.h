#pragma once

#include <stdio.h>

typedef struct choix choix_t, *choix_p;

//Lit un choix dans le fichier f (constructeur).
choix_p generer_choix(FILE* f);

//Alloue un tableau de length elements de type choix_p.
choix_p* choix_init_array(int length);


//Affiche le texte d'un choix.
void choix_afficher(choix_p this);


//Accesseur de l'attribut texte.
char* choix_get_texte(choix_p this);

//Accesseur de l'attribut page_suivante.
int choix_get_page_suivante(choix_p this);


//Destructeur de la structure choix_t.
void free_choix(choix_p this);