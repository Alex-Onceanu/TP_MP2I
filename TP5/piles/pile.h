#pragma once

#include <stdbool.h>

typedef char T;

/* Affiche dans le terminal l'element x de type T */
void affiche_element(T x);

typedef struct pile_ PILE;

/* Renvoie une pile vide */
PILE* pile_vide();

/* Renvoie un booléen indiquant si p est vide */
bool est_vide(PILE* p);

/* Empile x au sommet de p */
void empiler(PILE* p, T x);

/* Dépile le sommet de p et le renvoie */
T depiler(PILE* p);

/* Libère l'espace alloué à p */
void free_pile(PILE* p);

/* Affiche tous les elements de la pile à la verticale, le haut étant le sommet */
void affiche_pile(PILE* p);