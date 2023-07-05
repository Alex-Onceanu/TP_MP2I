#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "./archive/file.h"

// liste chainée pour les listes des voisins des sommets
typedef struct adj
{
	unsigned int voisin; // voisin stocké sur le maillon
	struct adj *suiv;	 // maillon suivant de la liste chaînée
} ADJ;

typedef struct
{
	int n;
	ADJ **lv; // listes des voisins
} GRAPHE;

void adj_free(ADJ *a)
{
	if (a == NULL)
		return;

	adj_free(a->suiv);
	free(a);
}

void graphe_free(GRAPHE *g)
{
	for (int i = 0; i < g->n; ++i)
	{
		adj_free(g->lv[i]);
	}
	free(g);
}

void print_graphe(GRAPHE *g)
{
	printf("Graphe a %d sommets:\n\n", g->n);
	ADJ *actuel = NULL;
	for (int i = 0; i < g->n; ++i)
	{
		printf("%d -> ", i);
		actuel = g->lv[i];
		while (actuel != NULL)
		{
			printf("%d, ", actuel->voisin);
			actuel = actuel->suiv;
		}
		printf("\n");
	}
}

bool trouve(GRAPHE *g, int i, int j)
{
	ADJ *actuel = g->lv[i];
	while (actuel != NULL)
	{
		if (actuel->voisin == j)
			return true;
		actuel = actuel->suiv;
	}
	return false;
}

void ajoute_arete(GRAPHE *g, int i, int j)
{
	ADJ *actuel = g->lv[i];

	while (actuel != NULL)
	{
		if (actuel->voisin == j)
			return;
		if (actuel->suiv == NULL)
		{
			actuel->suiv = malloc(sizeof(ADJ));
			actuel->suiv->voisin = j;
			actuel->suiv->suiv = NULL;
			return;
		}
		actuel = actuel->suiv;
	}
}

GRAPHE *construire_graphe(int n, int m, int **aretes, bool oriente)
{
	GRAPHE *res = malloc(sizeof(GRAPHE));
	res->lv = malloc(sizeof(ADJ *));
	res->n = n;

	for (int i = 0; i < m; ++i)
	{
		if (!trouve(res, aretes[i][0], aretes[i][1]))
			ajoute_arete(res, aretes[i][0], aretes[i][1]);

		if (!oriente && !trouve(res, aretes[i][0], aretes[i][1]))
			ajoute_arete(res, aretes[i][1], aretes[i][0]);
	}

	return res;
}

GRAPHE *lire_graphe(char *filename)
{
	FILE *fichier = fopen(filename, "r");
	if (fichier == NULL)
		return NULL;

	int m, n;
	fscanf(fichier, "%d %d", &n, &m);
	fgetc(fichier);
	int **aretes = malloc(m * sizeof(int *));
	for (int i = 0; i < m; ++i)
	{
		aretes[i] = malloc(2 * sizeof(int));
		fscanf(fichier, "%d %d", &(aretes[i][0]), &(aretes[i][1]));
	}
	GRAPHE *res = construire_graphe(n, m, aretes, true);

	for (int i = 0; i < m; ++i)
	{
		free(aretes[i]);
	}
	free(aretes);

	return res;
}

// résultat parcours en largeur
typedef struct
{
	int *d; // distances
	int *p; // prédécesseurs
} RES_PEL;

RES_PEL *parcours_largeur(GRAPHE *g, int s)
{
	RES_PEL *res = malloc(sizeof(RES_PEL));
	res->d = malloc(sizeof(int) * g->n);
	res->p = malloc(sizeof(int) * g->n);
	for (int i = 0; i < g->n; i++)
	{
		res->d[i] = -1;
		res->p[i] = -1;
	}

	FIFO *f = file_vide();
	enfiler(f, s);

	int u = s;
	res->d[u] = 0;
	while (!est_file_vide(f))
	{
		u = defiler(f);
		for (int v = 0; v < g->n; ++v)
		{
			if (res->d[v] == -1)
			{
				res->d[v] = res->d[u] + 1;
				res->p[v] = u;
				enfiler(f, v);
			}
		}
	}

	return res;
}

int *plus_court_chemin(GRAPHE *g, int s, int t)
{
	int *res = malloc(sizeof(int) * (g->n + 1));
	RES_PEL *r = parcours_largeur(g, s);

	int i = 0;
	int u = t;
	res[0] = t;
	while (u != s)
	{
		u = r->p[u];
		res[++i] = u;
	}

	// On renverse la liste pour parcourir le chemin dans le bon ordre
	int tmp = -1;
	for (int j = 0; j < i / 2; ++j)
	{
		tmp = res[i - j];
		res[i - j] = res[j];
		res[j] = tmp;
	}

	return res;
}

int main(int argc, char const *argv[])
{
	GRAPHE *g = malloc(sizeof(GRAPHE));
	g->n = 4;
	g->lv = malloc(4 * sizeof(ADJ *));

	// successeurs de 0: [1]
	g->lv[0] = malloc(sizeof(ADJ));
	g->lv[0]->voisin = 1;
	g->lv[0]->suiv = NULL;

	// successeurs de 1: [3]
	g->lv[1] = malloc(sizeof(ADJ));
	g->lv[1]->voisin = 3;
	g->lv[1]->suiv = NULL;

	// successeurs de 2: [0, 3, 1]
	g->lv[2] = malloc(sizeof(ADJ));
	g->lv[2]->voisin = 0;
	g->lv[2]->suiv = malloc(sizeof(ADJ));
	g->lv[2]->suiv->voisin = 3;
	g->lv[2]->suiv->suiv = malloc(sizeof(ADJ));
	g->lv[2]->suiv->suiv->voisin = 1;
	g->lv[2]->suiv->suiv->suiv = NULL;

	// successeurs de 3: [0]
	g->lv[3] = malloc(sizeof(ADJ));
	g->lv[3]->voisin = 0;
	g->lv[3]->suiv = NULL;

	print_graphe(g);

	graphe_free(g);

	return 0;
}