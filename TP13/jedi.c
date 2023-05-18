#include <assert.h>
#include <stdbool.h>
#include <string.h>

struct jedi {
	char* prenom;
	char* nom;
	struct jedi** apprentis;
	int n; // nombre d'apprentis
};

typedef struct jedi JEDI;


bool est_lignee(JEDI* j, char* prenom, char* nom){
	if (j == NULL){
		return false;
	}

	// test du noeud actuel
	// RAPPEL: strcmp(a, b) renvoie 0 si a et b sont égaux, un nombre négatif
	// si a < b dans l'ordre lexicographique, et un nombre positif si a > b
	// Pour plus d'informations: tapez "man strcmp" dans le terminal
	if (strcmp(prenom, j->prenom) == 0 && strcmp(nom, j->nom) == 0){
		return true;
	}

	// recherche récursive. On n'est pas dans une structure d'ABR donc
	// il faut chercher dans tous les enfants
	for (int i = 0; i < j->n; ++i)
	{
		if (est_lignee(j->apprentis[i], prenom, nom)){
			return true;
		}
	}
	
	return false;
}
