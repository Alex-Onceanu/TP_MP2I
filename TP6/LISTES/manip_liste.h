#pragma once

#include "liste.h"

//Renvoie la premiere place de l contenant x, ou NULL si introuvable.
PLACE* recherche(LISTE* l, int x);

//Supprime toutes les occurences de x dans l
void supprimer_occs(LISTE* l, int x);

