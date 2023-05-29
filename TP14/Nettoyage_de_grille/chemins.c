#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "chemins.h"
#include "grid.h"

char *chemin_aleatoire(GRID *g)
{
    int w = width(g);
    int h = height(g);
    int len = w + h - 2;
    char *res = malloc((1 + len) * sizeof(char));
    res[len] = '\0';
    int x = 0;
    int y = 0;

    for (int i = 0; i < len; ++i)
    {
        if (x == w - 1)
        {
            res[i] = 'D';
        }
        else if (y == h - 1)
        {
            res[i] = 'R';
        }
        else
        {
            if (rand() % 2)
            {
                res[i] = 'R';
                x++;
            }
            else
            {
                res[i] = 'D';
                y++;
            }
        }
    }

    return res;
}

bool choix_glouton(GRID *g, int i, int j)
{
    if (i == height(g) - 1)
        return true;
    if (j == width(g) - 1)
        return false;
    return get(g, j + 1, i) >= get(g, j, i + 1);
}

char *chemin_glouton(GRID *g)
{
    int len = width(g) + height(g) - 2;
    char *res = malloc((len + 1) * sizeof(char));
    res[len] = '\0';
    int x = 0;
    int y = 0;

    for (int i = 0; i < len; ++i)
    {
        if (choix_glouton(g, y, x))
        {
            x++;
            res[i] = 'R';
        }
        else
        {
            y++;
            res[i] = 'D';
        }
    }
    return res;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int **dechets_progdyn(GRID *g)
{
    // Initialisation du tableau de progdyn
    int h = height(g);
    int w = width(g);
    int **tab = malloc(h * sizeof(int *));
    for (int y = 0; y < h; ++y)
    {
        tab[y] = malloc(w * sizeof(int));
    }

    tab[0][0] = get(g, 0, 0);

    // Besoin de séparer ces 3 cas pour pas avoir plein de if
    // Faudrait vérifier qu'on sort pas du tableau à chaque itération, sinon

    // Premiere colonne
    for (int y = 1; y < h; ++y)
    {
        tab[y][0] = get(g, 0, y) + tab[y - 1][0];
    }
    // Premiere ligne
    for (int x = 1; x < w; ++x)
    {
        tab[0][x] = get(g, x, 0) + tab[0][x - 1];
    }
    // Tout le reste
    for (int x = 1; x < w; ++x)
    {
        for (int y = 1; y < h; ++y)
        {
            tab[y][x] = get(g, x, y) + max(tab[y - 1][x], tab[y][x - 1]);
        }
    }

    return tab;
}

// Reconstruit le chemin suivi pour aller de (0,0) à (x, y)
// À partir d'un tableau C de programmation dynamique
char *reconstruction_a_partir_de(int **C, GRID *g, int x, int y)
{
    int len = x + y;
    char *res = malloc((len + 1) * sizeof(char));
    res[len] = '\0';

    for (int i = len - 1; i >= 0; --i)
    {
        if (x == 0)
        {
            res[i] = 'D';
            y--;
        }
        else if (y == 0)
        {
            res[i] = 'R';
            x--;
        }
        else
        {
            if (C[y][x - 1] >= C[y - 1][x])
            {
                res[i] = 'R';
                x--;
            }
            else
            {
                res[i] = 'D';
                y--;
            }
        }
    }

    assert(x == 0 && y == 0);
    return res;
}

char *reconstruction(int **C, GRID *g)
{
    return reconstruction_a_partir_de(C, g, width(g) - 1, height(g) - 1);
}

int **dechets_contrainte_progdyn(GRID *g, int k)
{
    // Initialisation du tableau de progdyn
    int h = height(g);
    int w = width(g);
    int **tab = malloc(h * sizeof(int *));
    for (int y = 0; y < h; ++y)
    {
        tab[y] = malloc(w * sizeof(int));
    }

    tab[0][0] = get(g, 0, 0);

    // Besoin de séparer ces 3 cas pour pas avoir plein de if
    // Faudrait vérifier qu'on sort pas du tableau à chaque itération, sinon

    // Premiere colonne
    for (int y = 1; y < h; ++y)
    {
        tab[y][0] = get(g, 0, y) + tab[y - 1][0];
    }
    // Premiere ligne
    for (int x = 1; x < w; ++x)
    {
        tab[0][x] = get(g, x, 0) + tab[0][x - 1];
    }
    // Tout le reste
    for (int x = 1; x < w; ++x)
    {
        for (int y = 1; y < h; ++y)
        {
            if (tab[y - 1][x] + get(g, x, y) > k)
            {
                tab[y][x] = get(g, x, y) + tab[y][x - 1];
            }
            else if (tab[y][x - 1] + get(g, x, y) > k)
            {
                tab[y][x] = get(g, x, y) + tab[y - 1][x];
            }
            else
                tab[y][x] = get(g, x, y) + max(tab[y - 1][x], tab[y][x - 1]);
        }
    }

    return tab;
}

int trouver_max(int **C, int w, int h, int k, int *__x, int *__y)
{
    int M = 0;
    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            if (C[y][x] <= k && C[y][x] > M)
            {
                M = C[y][x];
                if (__x && __y)
                {
                    *__x = x;
                    *__y = y;
                }
            }
        }
    }
    return M;
}

char *reconstruction_contrainte(int **C, GRID *g, int k)
{
    int x = 0;
    int y = 0;

    // On cherche max { C[y][x] } ∩ [ 0, k ]
    // i.e la case
    trouver_max(C, width(g), height(g), k, &x, &y);

    // Puis on lance la reconstruction du parcours depuis cette case
    return reconstruction_a_partir_de(C, g, x, y);
}