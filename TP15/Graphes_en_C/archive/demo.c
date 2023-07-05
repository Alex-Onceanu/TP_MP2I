#include "stos.h"
#include "stof.h"
#include "adj_dict.h"
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>



/* Affiche les informations du graphe g sous le format suivant:
	 */
void print_graphe(GRAPHE* g){
	int n = taille(g);
	char** sommets = liste_sommets(g);
	for (int i = 0; i < n; ++i)
	{
		char* u = sommets[i];
		VOISIN* vois = premier_voisin(g, u);
		if (vois == NULL){
			// sommet sans voisins
			printf("%s\n", u);
		} else {
			// itérer sur les voisins
			printf("%s -> ", u);
			while (vois != NULL){
				// traiter le voisin actuel
				char* v = id_voisin(vois);
				float d = dist_voisin(vois);
				printf("(%s, %f), ", v, d);
				// passer au voisin suivant
				vois = voisin_suivant(vois);
			}
			printf("\n");
		}
	}
	// libérer la liste des sommets
	for (int i = 0; i < n; ++i)
	{
		free(sommets[i]);
	}
	free(sommets);
}



int main(int argc, char const *argv[])
{

	// test tables string to float

	// création nouvelle table
	STOF_TBL* tf = stof_tbl_vide();

	// ajout de correspondances (clé, valeur)
	stof_set(tf, "A", 23.2);
	stof_set(tf, "A", 5); // écrase l'ancienne valeur
	stof_set(tf, "B", 21.2);
	stof_set(tf, "C", 2);

	// récupérer la valeur associée à une clé
	assert(stof_get(tf, "A") == 5);

	// rechercher une clé
	assert(stof_mem(tf, "B"));
	assert(!stof_mem(tf, "TOTO"));

	// libérer la table
	stof_free(tf);


	// test tables string to string
	STOS_TBL* ts = stos_tbl_vide();
	stos_set(ts, "A", "Arbre");
	stos_set(ts, "A", "Abricot"); // écrase l'ancienne valeur
	stos_set(ts, "B", "Branche");
	stos_set(ts, "C", "Cerise");

	char* ka = stos_get(ts, "A"); // alloue de la mémoire pour le résultat
	assert(strcmp(ka, "Abricot") == 0);
	free(ka);

	assert(stos_mem(ts, "B")); 
	assert(!stos_mem(ts, "TOTO"));

	stos_free(ts);


	// test graphe
	GRAPHE* g = graphe_vide();
	ajouter_sommet(g, "A");
	ajouter_sommet(g, "B");
	ajouter_sommet(g, "C");
	ajouter_sommet(g, "D");
	ajouter_sommet(g, "TOTO");

	ajouter_arete(g, "A", "B", 5);
	ajouter_arete(g, "A", "C", 3);

	ajouter_arete(g, "B", "A", 4);
	ajouter_arete(g, "B", "D", 2);

	ajouter_arete(g, "C", "B", 1);
	ajouter_arete(g, "C", "C", 4);
	ajouter_arete(g, "C", "TOTO", 3);

	ajouter_arete(g, "D", "A", 4);
	ajouter_arete(g, "D", "C", 1);

	ajouter_arete(g, "TOTO", "B", 2);


	// afficher tous les sommets du graphe
	int n = taille(g);
	char** sommets = liste_sommets(g);
	for (int i = 0; i < n; ++i)
	{
		printf("%s\n", sommets[i]);
	}


	// libérer la mémoire
	for (int i = 0; i < n; ++i)
	{
		free(sommets[i]);
	}
	free(sommets);


	// affichage complet du graphe
	print_graphe(g);


	// itérer sur les voisins de "A"
	VOISIN* v = premier_voisin(g, "A");
	while (v != NULL){
		// traiter le voisin actuel
		char* id = id_voisin(v);
		float dist = dist_voisin(v);
		printf("Voici un voisin de A: %s. ", id);
		printf("L'arête (A, %s) est de poids %f\n", id, dist);
		// passer au voisin suivant
		v = voisin_suivant(v);
	}

	free_graphe(g);
	return 0;
}