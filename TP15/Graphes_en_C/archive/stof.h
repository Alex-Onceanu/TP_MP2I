/* Table de hachage string -> float 
   Les clés sont de type char*
   et les valeurs de type float
*/
#include "hash.h"
#include <stdbool.h>

#ifndef TAILLE_HASH
#define TAILLE_HASH 64783
unsigned int hash(char* s){
#endif


typedef struct stof_tbl STOF_TBL;

/* Crée une table de hachage string to string vide */
STOF_TBL* stof_tbl_vide();

/* Renvoie true si `clef` est une clef de t, false sinon */
bool stof_mem(STOF_TBL* t, char* clef);

/* Renvoie la valeur associée à `clef` dans t. Si
   t ne contient pas `clef`, affiche un message d'erreur
   et arrête l'exécution.

   La chaîne renvoyée est stockée dans une zone fraîchement
   allouée, il faut la libérer. */
float stof_get(STOF_TBL* t, char* clef);

/* Assigne à `clef` la valeur `valeur` dans t. Si
   `clef` est déjà présente, modifie la valeur précédente */
void stof_set(STOF_TBL* t, char* clef, float valeur);

/* Libère l'espace alloué pour la table t. */
void stof_free(STOF_TBL* t);