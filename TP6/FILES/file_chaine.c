#include "file.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


void affiche_element(T x)
{
    //pour char
    printf("%c", x);
}


typedef struct maillon{
    T elem;
    struct maillon* suivant;
}maillon_t;

struct file_{
    maillon_t* tete;
    maillon_t* queue;
};  

maillon_t* maillon(T val)
{
    maillon_t* resultat = malloc(sizeof(maillon_t));
    resultat->elem = val;
    resultat->suivant = NULL;
    return resultat;
}

FIFO* file_vide()
{
    FIFO* resultat = malloc(sizeof(FIFO));
    resultat->tete = NULL;
    resultat->queue = NULL;
    return resultat;
}

bool est_file_vide(FIFO* f)
{
    return f->tete == NULL;
}

void enfiler(FIFO* f, T x)
{
    maillon_t* m = maillon(x);
    
    if(est_file_vide(f))
    {
        f->tete = m;
        f->queue = m;
    }
    else
    {
        maillon_t* q = f->queue;
        q->suivant = m;
        f->queue = m;
    }
}

T defiler(FIFO* f)
{
    assert(!est_file_vide(f));
    maillon_t* ancien = f->tete;
    f->tete = ancien->suivant;
    T res = ancien->elem;

    free(ancien);
    return res;
}

void free_file(FIFO* f)
{
    maillon_t* curs = f->tete;
    while(curs != NULL)
    {
        maillon_t* ancien = curs;
        curs = curs->suivant;
        free(ancien);
    }
    free(f);
}

void affiche_file(FIFO* f)
{
    maillon_t* curs = f->tete;
    while(curs != NULL)
    {
        affiche_element(curs->elem);
        printf(", ");
        curs = curs->suivant;
    }
    printf("\n");
}