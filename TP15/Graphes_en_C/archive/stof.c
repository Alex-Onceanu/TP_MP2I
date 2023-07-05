#include "stof.h"
#include "hash.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct stof_maillon{
	char* clef;
	float valeur;
	struct stof_maillon* suiv;
} STOF_MAILLON;

typedef struct stof_tbl {
	STOF_MAILLON* table[TAILLE_HASH];
} STOF_TBL;


STOF_TBL* stof_tbl_vide(){
	STOF_TBL* t = malloc(sizeof(STOF_TBL));
	for (int i = 0; i < TAILLE_HASH; ++i)
	{
		t->table[i] = NULL;
	}
	return t;
}

bool stof_mem(STOF_TBL* t, char* clef){
	int h = hash(clef);
	STOF_MAILLON* m = t->table[h];
	// parcourir la liste chaînée jusqu'à trouver
	// la clef ou arriver à la fin
	while (m != NULL && strcmp(m->clef, clef) != 0){
		m = m->suiv;
	}
	return (m != NULL);
}


float stof_get(STOF_TBL* t, char* clef){
	int h = hash(clef);
	STOF_MAILLON* m = t->table[h];
	while (m != NULL && strcmp(m->clef, clef) != 0){
		m = m->suiv;
	}
	if (m == NULL){
		printf("Clé invalide: %s\n", clef);
		exit(1);
	} else {
		return (m->valeur);
	}
}

void stof_set(STOF_TBL* t, char* clef, float valeur){
	int h = hash(clef);
	STOF_MAILLON* m = t->table[h];
	while (m != NULL && strcmp(m->clef, clef) != 0){
		m = m->suiv;
	}
	if (m == NULL){
		m = malloc(sizeof(STOF_MAILLON));
		m->suiv = t->table[h];
		t->table[h] = m;
		m->clef = strdup(clef);
	}
	m->valeur = valeur;
}

void stof_free(STOF_TBL* t){
	for (int i = 0; i < TAILLE_HASH; ++i)
	{
		STOF_MAILLON* m = t->table[i];
		STOF_MAILLON* p = NULL;
		while (m != NULL){
			p = m;
			m = m->suiv;
			free(p->clef);
			free(p);
		}
	}
	free(t);
}