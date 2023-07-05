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

/* Maillon de la liste chaînée des voisins d'un sommet */
typedef struct voisin VOISIN;

// Graphe
typedef struct graphe GRAPHE;


/* Crée un graphe vide */
GRAPHE* graphe_vide();

/* Renvoie le nombre de sommets de g */
int taille(GRAPHE* g);

/* Renvoie la liste des sommets de g. Les chaînes renvoyées
	sont allouées dans de la mémoire fraîche, il faut les libérer
	ainsi que la liste elle même. */
char** liste_sommets(GRAPHE* g);

/* Ajoute au graphe g le sommet id. Si le sommet 
   est déjà présent, ne fait rien. */
void ajouter_sommet(GRAPHE* g, char* id);

/* Ajoute au graphe g l'arête (id1, id2) avec un poids `dist`.
   Les deux sommets doivent figurer dans g. Cette fonction
   ne vérifie pas si (i1, id2) est déjà une arête du graphe. */
void ajouter_arete(GRAPHE* g, char* id1, char* id2, float dist);

/* Renvoie un pointeur vers le premier voisin de id dans g 
   dans l'ordre de stockage */
VOISIN* premier_voisin(GRAPHE* g, char* id);

/* Renvoie le nom du sommet d'arrivée de l'arête représentée par v.
   Il ne faut PAS appeler free sur le résultat de cette fonction
   car le pointeur renvoyé est égal à celui stocké dans la structure GRAPHE */
char* id_voisin(VOISIN* v);

/* Renvoie le poids de l'arête représentée par v */
float dist_voisin(VOISIN* v);

/* Renvoie le voisin suivant v, NULL si v est le dernier
	voisin dans l'ordre de stockage. */
VOISIN* voisin_suivant(VOISIN* v);

/* Libère la mémoire allouée pour le graphe g */
void free_graphe(GRAPHE* g);

/* Affiche les informations basiques de g, sous la forme:
	
	sommetA -> (voisinA1, poidsA1), (voisinA2, poidsA2), ...
	sommetB -> (voisinB1, poidsB1), ... 
	
*/
void print_graphe(GRAPHE* g);