#include <stdbool.h>
#pragma once

typedef char T;

//Fonction propre au type T, permet d'écrire x dans le terminal
void affiche_element(T x);

typedef struct file_ FIFO;

//Constructeur de la structure FIFO
FIFO* file_vide();

//Renvoie true si f ne contient aucun élément, false sinon
bool est_file_vide(FIFO* f);

//Ajoute un élément x au début de la file f
void enfiler(FIFO* f, T x);

//Renvoie l'élément au bout de la file, selon le principe "FIFO"
T defiler(FIFO* f);

//Destructeur de la structure FIFO
void free_file(FIFO* f);

//Affiche chaque élément de f grâce à la fonction "affiche_element()"
void affiche_file(FIFO* f);