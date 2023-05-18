#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tas.h"

/* Échange les noeuds i et j de t */
void swap(HEAP *t, int i, int j)
{
    assert(0 <= i && 0 <= j && i < t->taille_actuelle && j < t->taille_actuelle);
    T tmp = t->tab[i];
    t->tab[i] = t->tab[j];
    t->tab[j] = tmp;
}

HEAP *tas_vide(int taille)
{
    HEAP *res = malloc(sizeof(HEAP));

    res->taille_actuelle = 0;
    res->taille_max = taille;
    res->tab = malloc(taille * sizeof(T));

    return res;
}

int pere(int i)
{
    return (i - 1) / 2;
}

int gauche(int i)
{
    return 2 * i + 1;
}

int droite(int i)
{
    return 2 * i + 2;
}

void tasser(HEAP *t, int i)
{
    T tmp;
    while (i > 0)
    {
        if (t->tab[pere(i)] > t->tab[i])
            break;

        swap(t, i, pere(i));

        i = pere(i);
    }
}

void tamiser(HEAP *t, int i)
{
    T tmp;
    while (gauche(i) < t->taille_actuelle || droite(i) < t->taille_actuelle)
    {
        if (t->tab[gauche(i)] < t->tab[i] && t->tab[droite(i)] < t->tab[i])
            break;

        if (droite(i) < t->taille_actuelle)
        {
            if (t->tab[gauche(i)] > t->tab[droite(i)])
            {
                swap(t, i, gauche(i));
                i = gauche(i);
            }
            else
            {
                swap(t, i, droite(i));
                i = droite(i);
            }
        }
        else
        {
            // Ici forcément gauche(i) < t->taille_actuelle
            swap(t, i, gauche(i));
            i = gauche(i);
        }
    }
}

void ajouter(HEAP *t, T x)
{
    if (t->taille_actuelle >= t->taille_max)
    {
        t->taille_max *= 2;
        t->tab = realloc(t->tab, t->taille_max * sizeof(T));
    }
    int i = 0;
    t->tab[t->taille_actuelle] = x;
    tasser(t, t->taille_actuelle++);
}

T extraire_max(HEAP *t)
{
    T res = t->tab[0];
    swap(t, 0, t->taille_actuelle - 1);

    t->taille_actuelle--;
    tamiser(t, 0);

    return res;
}

void augmenter(HEAP *t, int i, T y)
{
    t->tab[i] = y;
    tasser(t, i);
}

void tri_par_tas(int *t, int n)
{
    HEAP *res = malloc(sizeof(HEAP));

    res->tab = t;
    res->taille_actuelle = 0;
    res->taille_max = n;

    while (res->taille_actuelle < n)
    {
        tasser(res, res->taille_actuelle++);
    }
    int tmp;
    while (res->taille_actuelle > 0)
    {
        extraire_max(res);
    }
    res->taille_actuelle = n;
}
