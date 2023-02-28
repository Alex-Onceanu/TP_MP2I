#pragma once

#include <stdbool.h>

typedef int T;

typedef struct place {
	T elem;
	struct place* suiv;
	struct place* prec;
} PLACE;

typedef struct liste{
	PLACE* tete;	//pointeur vers le premier élément
	PLACE* queue;	//pointeur vers le dernier élément de la liste
	int taille;
} LISTE;


//Fonction propre au type T, pour écrire un élément x de type T dans stdout
void affiche_elem(T x);

//Constructeur de la structure LISTE
LISTE* creer_liste();

//Renvoie le nombre d'éléments contenus dans l
int taille(LISTE* l);

//Renvoie Laplace du premier élément de l
PLACE* tete(LISTE* l);

//Renvoie la place du dernier élément de l
PLACE* queue(LISTE* l);

//Renvoie le contenu d'une place (accesseur)
T contenu(PLACE* p);

//Le contenu d'une place devient x (mutateur)
void modifier(PLACE* p, T x);

//Renvoie la place suivante d'une place
PLACE* suivant(PLACE* p);

//Renvoie la place précédente d'une place
PLACE* precedent(PLACE* p);

//Insere un élément x avant une place p
void inserer(LISTE* l, PLACE* p, T x);

//Supprime une place inplace
void supprimer(LISTE* l, PLACE* p);

//Ajoute un element x a la fin de l
void ajouter(LISTE* l, T x);

//Affiche tous les elements de l grâce à la fonction "affiche_elem()"
void affiche_liste(LISTE* l);

//Destructeur de la structure LISTE
void free_liste(LISTE* l);

//Renvoie true si l contient 0 elements, false sinon
bool est_vide(LISTE* l);