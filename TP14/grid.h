#pragma once

typedef struct grid_t GRID;

// Constructeur, depuis un fichier
GRID *lire_grille(char *filename);
// Destructeur
void GRID_free(GRID *this);

// Accesseur de g->w
int width(const GRID *this);
// Accesseur de g->h
int height(const GRID *this);
// Accesseur de la case de coordonnées y, x
int get(const GRID *this, int x, int y);
// Mutateur de la case de coordonnées y, x
void set(GRID *this, int val, int x, int y);

// Affiche la grille dans stdout
void GRID_print(const GRID *this);

// Calcule la somme des coefficients du chemin
int valeur(GRID *g, char *chemin);
