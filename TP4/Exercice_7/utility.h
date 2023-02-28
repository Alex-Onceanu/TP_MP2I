#pragma once

#include <stdbool.h>

//Nombre maximal de caracteres dans une ligne du fichier .txt de l'histoire.
#define MAX_LENGTH 600

//Lit une ligne du fichier f dans str.
//S'arrete au premier \n, et le remplace par un \0.
//Renvoie true si on arrive a la fin de f, false sinon
bool fscan_ligne(FILE* f, char* str);


//Comme scanf, mais en mieux.
//Affiche d'abord le message, puis attend une reponse.
//Renvoie un entier dans [| borne_min, borne_max |]
int meilleur_scanf(char* message, int borne_min, int borne_max);