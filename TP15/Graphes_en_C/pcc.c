#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// liste chainée pour les listes des voisins des sommets
typedef struct adj
{
    unsigned int voisin; // voisin stocké sur le maillon
    float w;             // distance (pondération de l'arête en question)
    struct adj *suiv;    // maillon suivant de la liste chaînée
} ADJ;

typedef struct ladj
{
    int n;
    ADJ **lv; // listes des voisins
} LADJ;

void adj_free(ADJ *a)
{
    if (a == NULL)
        return;

    adj_free(a->suiv);
    free(a);
}

void ladj_free(LADJ *g)
{
    for (int i = 0; i < g->n; ++i)
    {
        adj_free(g->lv[i]);
    }
    free(g);
}

typedef struct madj
{
    int n;
    float **tab;
} MADJ;

MADJ *to_MADJ(LADJ *l)
{
    MADJ *res = malloc(sizeof(MADJ));
    res->n = l->n;
    res->tab = malloc(res->n * sizeof(float *));

    ADJ *actuel = NULL;
    for (int i = 0; i < l->n; ++i)
    {
        res->tab[i] = malloc(res->n * sizeof(float));

        actuel = l->lv[i];
        while (actuel != NULL)
        {
            res->tab[i][actuel->voisin] = actuel->w;
            actuel = actuel->suiv;
        }
    }

    ladj_free(l);
    return res;
}

LADJ *to_LADJ(MADJ *m)
{
    LADJ *res = malloc(sizeof(LADJ));
    res->n = m->n;
    res->lv = malloc(sizeof(ADJ *) * res->n);

    ADJ *actuel = NULL;
    ADJ *verif = NULL;
    for (int y = 0; y < m->n; ++y)
    {
        res->lv[y] = malloc(sizeof(ADJ));
        actuel = res->lv[y];
        verif = actuel;
        for (int x = 0; x < m->n; ++x)
        {
            if (m->tab[y][x] != 0)
            {
                actuel->voisin = x;
                actuel->w = m->tab[y][x];
                actuel->suiv = malloc(sizeof(ADJ)); // On alloue à l'avance le suivant, quitte à free
                actuel = actuel->suiv;
            }
        }
        free(actuel);
        if (verif == actuel)
        {
            // Cas où un sommet n'a aucun voisin..
            free(actuel);
            res->lv[y] = NULL;
        }
        // On free aussi la ligne actuelle, tant qu'on y est
        free(m->tab[y]);
    }
    free(m->tab);
    free(m);

    return res;
}

// Mij0 = INFINITY

float **floyd_warshall(MADJ *g)
{
    float **res = malloc(sizeof(float *));
    for (int y = 0; y < g->n; ++y)
    {
        res[y] = malloc(g->n * sizeof(float *));
        for (int x = 0; x < g->n; ++x)
        {
            res[y][x] = g->tab[y][x];
        }
    }

    for (int i = 0; i < g->n; ++i)
    {
        for (int j = 0; j < g->n; ++j)
        {
            for (int k = 0; k < g->n; ++k)
            {
                if (res[i][k] + res[k][j] < res[i][j])
                {
                    res[i][j] = res[i][k] + res[k][j];
                }
            }
        }
    }
    return res;
}

typedef struct
{
    int *d;
    int *pred;
} RES_DIJK;

bool est_vide(int *q, int n)
{
    for (int i = 0; i < n; ++i)
    {
        if (q[i] != -1)
            return false;
    }
    return true;
}

RES_DIJK dijsktra(LADJ *g, int s)
{
    RES_DIJK res;
    res.d = malloc(g->n * sizeof(g->n));
    res.pred = malloc(g->n * sizeof(g->n));

    for (int i = 0; i < g->n; ++i)
    {
        res.d[i] = INFINITY;
        res.pred[i] = -1;
    }

    res.d[s] = 0;
    int *q = malloc(g->n * sizeof(int));
    for (int i = 0; i < g->n; ++i)
    {
        q[i] = i;
    }
    int u;
    int minloc;
    while (!est_vide(q, g->n))
    {
        // On cherche u, élément de q avec d[u] minimal et != -1
        minloc = INFINITY;
        for (int i = 0; i < g->n; ++i)
        {
            if (res.d[i] < minloc && q[i] != -1)
            {
                u = i;
                minloc = res.d[i];
            }
        }
        q[u] = -1;
        // u est extrait

        for (ADJ *v = g->lv[u]; v != NULL; v = v->suiv)
        {
            if (res.d[u] + v->w < res.d[v->voisin])
            {
                res.d[v->voisin] = res.d[u] + v->w;
                res.pred[v->voisin] = u;
            }
        }
    }

    return res;
}

int *pcc(LADJ *g, int s, int t)
{
    int *res = malloc(sizeof(int) * (g->n + 1));
    RES_DIJK r = dijsktra(g, s);

    int i = 0;
    int u = t;
    res[0] = t;
    while (u != s)
    {
        u = r.pred[u];
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

int main(int argc, char **argv)
{
    // Tests à faire...

    return 0;
}