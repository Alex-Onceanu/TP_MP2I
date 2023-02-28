#pragma once

#include <stdbool.h>

#include "liste.h"

//Renvoie une liste contenant tous les elements des listes de ls
LISTE* concatenation(LISTE** ls, int n);

//Renvoie une liste de 3 elements :
//une liste contenant les elements plus petits que le pivot (i.e x),
//une pour les elements egaux a x et une pour les elements plus grands.
LISTE** separer(LISTE* l, int x);

//Cree une liste avec n entiers aleatoires compris dans [0, 100]
//Cette fonction necessite d'avoir deja appele srand() auprealablement.
LISTE* aleatoire(int n);

//Renvoie true si l est dans l'ordre croissant selon <= sur int, false sinon.
bool est_triee(LISTE* l);

//Renvoie une copie de l triee dans l'ordre croissant
LISTE* tri_rapide(LISTE* l);