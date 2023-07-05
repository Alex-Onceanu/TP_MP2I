#include "stos.h"
#include "hash.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct stos_maillon{
	char* clef;
	char* valeur;
	struct stos_maillon* suiv;
} STOS_MAILLON;

typedef struct stos_tbl {
	STOS_MAILLON* table[TAILLE_HASH];
} STOS_TBL;


STOS_TBL* stos_tbl_vide(){
	STOS_TBL* t = malloc(sizeof(STOS_TBL));
	for (int i = 0; i < TAILLE_HASH; ++i)
	{
		t->table[i] = NULL;
	}
	return t;
}

bool stos_mem(STOS_TBL* t, char* clef){
	int h = hash(clef); // indice de la case de la clef
	STOS_MAILLON* m = t->table[h];
	// parcourir la liste chaînée jusqu'à trouver
	// la clef ou arriver à la fin
	while (m != NULL && strcmp(m->clef, clef) != 0){
		m = m->suiv;
	}
	return (m != NULL);
}


char* stos_get(STOS_TBL* t, char* clef){
	int h = hash(clef);
	STOS_MAILLON* m = t->table[h];
	while (m != NULL && strcmp(m->clef, clef) != 0){
		m = m->suiv;
	}
	if (m == NULL){
		printf("Clé invalide: %s\n", clef);
		exit(1);
	} else { // copier la valeur dans une nouvelle case mémoire
		return (strdup(m->valeur));
	}
}

void stos_set(STOS_TBL* t, char* clef, char* valeur){
	int h = hash(clef);
	STOS_MAILLON* m = t->table[h];
	while (m != NULL && strcmp(m->clef, clef) != 0){
		m = m->suiv;
	}
	if (m == NULL){
		// créer un nouveau maillon
		m = malloc(sizeof(STOS_MAILLON));
		m->suiv = t->table[h];
		t->table[h] = m;
		m->clef = strdup(clef);
	} else { // libérer l'ancienne valeur avant de l'écraser
		free(m->valeur);
	}
	m->valeur = strdup(valeur);
}

void stos_free(STOS_TBL* t){
	for (int i = 0; i < TAILLE_HASH; ++i)
	{
		STOS_MAILLON* m = t->table[i];
		STOS_MAILLON* p = NULL;
		while (m != NULL){
			p = m;
			m = m->suiv;
			free(p->clef);
			free(p->valeur);
			free(p);
		}
	}
	free(t);
}