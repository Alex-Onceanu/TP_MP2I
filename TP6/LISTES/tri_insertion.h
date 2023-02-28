#pragma once

#include <stdbool.h>

#include "liste.h"


//Insere x dans l (au bon endroit) en supposant que l est triee dans l'ordre croissant
void insertion_triee(LISTE* l, int x);

//Cree une liste avec n entiers aleatoires compris dans [0, 100]
//Cette fonction necessite d'avoir deja appele srand() auprealablement.
LISTE* aleatoire2(int n);

//Renvoie true si l est dans l'ordre croissant selon <= sur int, false sinon.
bool est_triee2(LISTE* l);

//Renvoie une copie de l triee dans l'ordre croissant
LISTE* tri_insertion(LISTE* l);