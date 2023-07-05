/* Dictionnaire d'adjacence par table de hachage 
	4 classes:
	- GRAPHE est un tableau de listes d'ITEM,
	  dont certaines vides, correspondant aux
	  listes chaînées de la table de hachage. 
	
	- chaque ITEM correspond à un sommet du graphe,
	  il comporte un SOMMET et un pointeur vers l'iTEM
	  suivant.

	- chaque SOMMET a un identifiant, qui est le nom
	  du sommet, et une liste chaînée de VOISINs.
	  Un sommet d'identifiant id sera dans la case
	  d'indice hash(id) du tableau d'un graphe
	
	- chaque VOISIN a un identifiant, ainsi qu'une
	  distance indiquant le poids de l'arête concernée.
*/
#include "adj_dict.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* Maillon de la liste des voisins d'un sommet */
typedef struct voisin {
	char* id; // identifiant 
	float dist; // poids de l'arête
	struct voisin* suiv; // maillon suivant
} VOISIN;


/* Information d'un sommet */
typedef struct {
	char* id;
	VOISIN* premier_voisin; // premier voisin
} SOMMET;


// Maillon dans la table de hachage du dictionnaire d'adjacence
typedef struct item  {
	SOMMET* sommet;
	struct item* suiv;
} ITEM;



// Dictionnaire d'adjacence par table de hachage
typedef struct graphe {
	ITEM* table[TAILLE_HASH];
} GRAPHE;



GRAPHE* graphe_vide(){
	GRAPHE* g = malloc(sizeof(GRAPHE));
	for (int i = 0; i < TAILLE_HASH; ++i)
	{
		g->table[i] = NULL;
	}
}

int taille(GRAPHE* g){
	int res = 0;
	for (int i = 0; i < TAILLE_HASH; ++i)
	{
		for (ITEM* it = g->table[i]; it != NULL; it = it->suiv){
			res++;
		}
	}
	return res;
}

char** liste_sommets(GRAPHE* g){
	int n = taille(g);
	char** res = malloc(sizeof(char*)*n);

	int j = 0; // indice courant de la liste résultat
	for (int i = 0; i < TAILLE_HASH; ++i)
	{
		for (ITEM* it = g->table[i]; it != NULL; it = it->suiv){
			res[j] = strdup(it->sommet->id);
			j++;
		}
	}
	return res;	
}

/* Renvoie le SOMMET associé à id dans g, NULL si id n'est pas
	un sommet de g */
SOMMET* trouver_sommet(GRAPHE* g, char* id){
	int h = hash(id);
	ITEM* it = g->table[h];
	while (it != NULL && strcmp(it->sommet->id, id) != 0){
		it = it->suiv;
	}
	if (it == NULL){
		return NULL;
	}
	return it->sommet;
}

void ajouter_sommet(GRAPHE* g, char* id){
	SOMMET* s = trouver_sommet(g, id);
	if (s != NULL){
		printf("Avertissement: sommet %s déjà présent\n", id);
		return;
	}
	int h = hash(id);
	ITEM* head = g->table[h];
	g->table[h] = malloc(sizeof(ITEM));
	g->table[h]->suiv = head;
	g->table[h]->sommet = malloc(sizeof(SOMMET));
	g->table[h]->sommet->id = strdup(id);
	g->table[h]->sommet->premier_voisin = NULL;
}

void ajouter_arete(GRAPHE* g, char* id1, char* id2, float dist){
	SOMMET* s1 = trouver_sommet(g, id1);
	if (s1 == NULL){
		printf("Sommet invalide: %s\n", id1);
		return;
	}
	SOMMET* s2 = trouver_sommet(g, id2);
	if (s2 == NULL){
		printf("Sommet invalide: %s\n", id2);
		return;
	}

	// mise à jour liste chaînée
	VOISIN* head = s1->premier_voisin;
	s1->premier_voisin = malloc(sizeof(VOISIN));
	s1->premier_voisin->id = strdup(id2);
	s1->premier_voisin->dist = dist;
	s1->premier_voisin->suiv = head;
}


VOISIN* premier_voisin(GRAPHE* g, char* id){
	SOMMET* s = trouver_sommet(g, id);
	if (s == NULL){
		printf("Sommet invalide: %s\n", id);
		return NULL;
	}
	return s->premier_voisin;
}

char* id_voisin(VOISIN* v){
	if (v == NULL){
		printf("Avertissement: id_voisin appelé sur NULL\n");
		return NULL;
	}
	return v->id;
}

float dist_voisin(VOISIN* v){
	if (v == NULL){
		printf("Avertissement: id_voisin appelé sur NULL\n");
		return 0;
	}
	return v->dist;
}

VOISIN* voisin_suivant(VOISIN* v){
	if (v == NULL){
		printf("Avertissement: voisin_suivant appelé sur NULL\n");
		return NULL;
	}
	return v->suiv;
}

void free_sommet(SOMMET* u){
	free(u->id);
	VOISIN* v = u->premier_voisin;
	VOISIN* prev = NULL;
	while (v != NULL){
		prev = v;
		v = v->suiv;
		free(prev->id);
		free(prev);
	}
	free(u);
}


void free_graphe(GRAPHE* g){
	for (int i = 0; i < TAILLE_HASH; ++i)
	{
		ITEM* it = g->table[i];
		ITEM* prev = NULL;
		while (it != NULL){
			prev = it;
			it = it->suiv;
			free_sommet(prev->sommet);
			free(prev);
		}
	}
	free(g);
}
