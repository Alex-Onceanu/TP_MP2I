/* Table de hachage string -> string 
   Les clés et les valeurs sont de type char*
*/
#include "hash.h"
#include <stdbool.h>

typedef struct stos_tbl STOS_TBL;

/* Crée une table de hachage string to string vide */
STOS_TBL* stos_tbl_vide();

/* Renvoie true si `clef` est une clef de t, false sinon */
bool stos_mem(STOS_TBL* t, char* clef);

/* Renvoie la valeur associée à `clef` dans t. Si
   t ne contient pas `clef`, affiche un message d'erreur
   et arrête l'exécution.

   La chaîne renvoyée est stockée dans une zone fraîchement
   allouée, il faut la libérer. */
char* stos_get(STOS_TBL* t, char* clef);

/* Assigne à `clef` la valeur `valeur` dans t. Si
   `clef` est déjà présente, modifie la valeur précédente */
void stos_set(STOS_TBL* t, char* clef, char* valeur);

/* Libère l'espace alloué pour la table t. */
void stos_free(STOS_TBL* t);