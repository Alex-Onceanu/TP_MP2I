#include <stdbool.h>
#include <stdio.h>
#pragma once

typedef struct file_ FIFO;

/* Renvoie une file vide */
FIFO *file_vide();

/* Renvoie un booléen indiquant si f est vide */
bool est_file_vide(FIFO *f);

/* Enfile x à la queue de f */
void enfiler(FIFO *f, int x);

/* Défile la tête de f et la renvoie */
int defiler(FIFO *f);

/* Libère l'espace alloué à f */
void free_file(FIFO *f);

void affiche_file(FIFO *f);