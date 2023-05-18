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