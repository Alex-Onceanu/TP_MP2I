#pragma once

#include <stdbool.h>

#include "grid.h"

// Génère un chemin aléatoire entre (0, 0) et (n-1, m-1)
char *chemin_aleatoire(GRID *g);

//_________________________ Glouton ______________________

// Élabore un choix gloutonnesque (true = droite)
bool choix_glouton(GRID *g, int i, int j);

// Élabore un chemin de choix gloutonnesques
char *chemin_glouton(GRID *g);

// Élabore un tableau de possibilités dynamiques
int **dechets_progdyn(GRID *g);

// Construit un chemin à partir d'un tableau progdyn
char *reconstruction(int **C, GRID *g);

// Partie bonus : on a un sac de contenance maximale k
int **dechets_contrainte_progdyn(GRID *g, int k);

// Renvoie M, plus grand élément de C parmi les éléments <= k
// __x, __y prennent la valeur des coordonnées de M
// C est supposé de taille w * h (w = width, h = height)
int trouver_max(int **C, int w, int h, int k, int *__x, int *__y);

// Reconstruit un chemin à partir d'un tableau progdyn avec |sac| = k
char *reconstruction_contrainte(int **C, GRID *g, int k);