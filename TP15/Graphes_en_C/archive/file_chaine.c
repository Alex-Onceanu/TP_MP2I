#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "file.h"

/* Implémentation des files par liste chaînée */

typedef struct maillon
{
	int elem;
	struct maillon *suivant;   // suivant est derrière
	struct maillon *precedent; // précédent est devant
} MAILLON;

struct file_
{
	MAILLON *tete;
	MAILLON *queue;
};

FIFO *file_vide()
{
	printf("Création d'une file implémentée par liste chainée\n");
	FIFO *f = malloc(sizeof(FIFO));
	f->tete = NULL;
	f->queue = NULL;
	return f;
}

bool est_file_vide(FIFO *f)
{
	return (f->tete == NULL);
}

void enfiler(FIFO *f, int x)
{
	MAILLON *m = f->queue;
	MAILLON *nouv_q = malloc(sizeof(MAILLON));

	nouv_q->elem = x;
	nouv_q->suivant = NULL;
	nouv_q->precedent = m;

	if (m != NULL)
	{
		m->suivant = nouv_q;
	}

	f->queue = nouv_q;
	if (f->tete == NULL)
	{
		f->tete = nouv_q;
	}
}

int defiler(FIFO *f)
{
	assert(!est_vide(f));
	MAILLON *m = f->tete;
	int res = m->elem;

	MAILLON *nouv_t = f->tete->suivant;

	if (nouv_t != NULL)
	{
		nouv_t->precedent = NULL;
	}

	if (f->tete == f->queue)
	{ // cas limite ou il n'y a qu'un élément
		f->queue = nouv_t;
	}
	f->tete = nouv_t;

	free(m); // éviter les fuites mémoire
	return res;
}

void free_maillon(MAILLON *m)
{
	if (m != NULL)
	{
		free_maillon(m->suivant);
		free(m);
	}
}

void free_file(FIFO *f)
{
	free_maillon(f->tete);
	free(f);
}

void affiche_file(FIFO *f)
{
	printf("Etat de la file:\n");
	for (MAILLON *m = f->tete; m != NULL; m = m->suivant)
	{
		printf("%c ", m->elem);
	}
	printf("\n");
}