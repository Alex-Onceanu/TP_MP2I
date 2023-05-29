#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "grid.h"

struct grid_t
{
    int w;
    int h;
    int *tab;
};

int width(const GRID *this)
{
    return this->w;
}

int height(const GRID *this)
{
    return this->h;
}

int get(const GRID *this, int x, int y)
{
    return this->tab[y * this->w + x];
}

void set(GRID *this, int val, int x, int y)
{
    this->tab[y * this->w + x] = val;
}

GRID *lire_grille(char *filename)
{
    FILE *fichier = fopen(filename, "r");
    GRID *res = malloc(sizeof(GRID));

    fscanf(fichier, "%d %d", &res->h, &res->w);
    res->tab = malloc(res->w * res->h * sizeof(int));
    int tmp = 0;

    for (int y = 0; y < res->h; ++y)
    {
        for (int x = 0; x < res->w; ++x)
        {
            fscanf(fichier, "%d", &tmp);
            set(res, tmp, x, y);
        }
    }

    fclose(fichier);

    return res;
}

void GRID_free(GRID *this)
{
    free(this->tab);
    free(this);
}

void GRID_print(const GRID *this)
{
    for (int y = 0; y < this->h; ++y)
    {
        for (int x = 0; x < this->w; ++x)
        {
            printf("%3d", get(this, x, y));
        }
        printf("\n");
    }
}

int valeur(GRID *g, char *chemin)
{
    assert(chemin != NULL);

    int res = get(g, 0, 0);
    int x = 0;
    int y = 0;
    int len = g->w + g->h - 2;
    bool probleme = false;

    for (int i = 0; i < len; ++i)
    {
        switch (chemin[i])
        {
        case 'D':
            y++;
            break;
        case 'R':
            x++;
            break;
        default:
            probleme = true;
            break;
        }
        probleme = probleme || x < 0 || x >= g->w || y < 0 || y >= g->h;

        if (probleme)
        {
            printf("un message d'avertissement\n");
            return -1;
        }
        res += get(g, x, y);
    }

    return res;
}
