#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "file.h"


#define Nmax 10
struct file_{
    int nb_elem;
    int queue;
    T* tab;
};

void affiche_element(T x)
{
    printf("%c", x);
}

FIFO* file_vide()
{
    FIFO* resultat = malloc(sizeof(FIFO));
    resultat->tab = malloc(Nmax * sizeof(T));
    resultat->nb_elem = 0;
    resultat->queue = 0;
    return resultat;
}

bool est_file_vide(FIFO* f)
{
    return f->nb_elem == 0;
}

void enfiler(FIFO* f, T x)
{
    assert(f->nb_elem < Nmax);
    f->tab[f->queue] = x;
    f->queue = (f->queue + 1) % Nmax;
    f->nb_elem++;
}

T defiler(FIFO* f)
{
    return f->tab[f->queue - f->nb_elem--];
}

void free_file(FIFO* f)
{
    free(f->tab);
    free(f);
}

void affiche_file(FIFO* f)
{
    T elem;
    for(int i = 0; i < f->nb_elem; ++i)
    {
        elem = defiler(f);
        affiche_element(elem);
        printf(", ");
        enfiler(f, elem);
    }
}