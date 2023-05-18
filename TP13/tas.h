#pragma once

#define T int

// On implémente les TAS_MAX
typedef struct tas_
{
    T *tab;
    int taille_max;
    int taille_actuelle;
} HEAP;

// père du noeud i
int pere(int i);

// fils gauche du noeud i
int gauche(int i);

// fils droit du noeud i
int droite(int i);

/* Crée et renvoie un tas vide de taille `taille`. */
HEAP *tas_vide(int taille);

// tasse
void tasser(HEAP *t, int i);

// tamise
void tamiser(HEAP *t, int i);

/* Ajoute x dans t. t ne doit pas être plein. */
void ajouter(HEAP *t, T x);

/* Renvoie la valeur maximale de t. t doit être non vide. */
T extraire_max(HEAP *t);

/* modifie la priorité du noeud i avec la valeur y.
   y doit être inférieur à la priorité actuelle
   de i. t doit être un tas-max: augmenter la priorité
   d'un noeud revient à augmenter son étiquette */
void augmenter(HEAP *t, int i, T y);

/* Trie en place le tableau t de taille n en utilisant
   un tas. */
void tri_par_tas(int *t, int n);
