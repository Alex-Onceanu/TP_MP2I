#include "liste.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void affiche_elem(T x)
{
    printf("%d", x);
}

LISTE* creer_liste()
{
    LISTE* resultat = malloc(sizeof(LISTE));

    resultat->taille = 0;
    resultat->tete = NULL;
    resultat->queue = NULL;

    return resultat;
}

int taille(LISTE* l)
{
    assert(l != NULL);
    return l->taille;
}

PLACE* tete(LISTE* l)
{
    assert(l != NULL);
    return l->tete;
}

PLACE* queue(LISTE* l)
{
    assert(l != NULL);
    return l->queue;
}

T contenu(PLACE* p)
{
    assert(p != NULL);
    return p->elem;
}

void modifier(PLACE* p, T x)
{
    assert(p != NULL);
    p->elem = x;
}

PLACE* suivant(PLACE* p)
{
    assert(p != NULL);
    return p->suiv;
}

PLACE* precedent(PLACE* p)
{
    assert(p != NULL);
    return p->prec;
}

void inserer(LISTE* l, PLACE* p, T x)
{
    assert(l != NULL && p != NULL);
    PLACE* nouv = malloc(sizeof(PLACE));
    nouv->elem = x;
    PLACE* po = p->prec;
    if(p == l->tete)
    {
        l->tete = nouv;
    }
    else
    {
        po->suiv = nouv;
    }
    nouv->suiv = p;
    p->prec = nouv;
    nouv->prec = po;
    l->taille++;
}

void supprimer(LISTE* l, PLACE* p)
{
    assert(l != NULL && p != NULL);
    if(p == l->tete)
    {
        l->tete = p->suiv;
        if(l->tete != NULL)
        {
            l->tete->prec = NULL;
        }
    }
    else if(p == l->queue)
    {
        l->queue = p->prec;
        if(l->queue != NULL)
        {
            l->queue->suiv = NULL;
        }
    }
    else
    {
        p->prec->suiv = p->suiv;
        p->suiv->prec = p->prec;
    }
    free(p);
    l->taille--;
}

void ajouter(LISTE* l, T x)
{
    PLACE* p = malloc(sizeof(PLACE));
    p->elem = x;
    p->prec = l->queue;
    p->suiv = NULL;

    if(l->queue != NULL)
    {
        l->queue->suiv = p;
    }

    l->queue = p;
    if(l->tete == NULL)
    {
        l->tete = p;
    }
    l->taille++;
}

void affiche_liste(LISTE* l)
{
    assert(l != NULL);
    PLACE* curs = l->tete;
    printf("[");
    for(int i = 0; i < l->taille - 1; ++i)
    {
        affiche_elem(contenu(curs));
        printf(" -> ");
        curs = curs->suiv;
    }
    if(l->taille != 0) affiche_elem(contenu(l->queue));
    printf("]\n");
}

void free_liste(LISTE* l)
{
    assert(l != NULL);
    PLACE* curs = l->tete;
    PLACE* s;
    for(int i = 0; i < l->taille; ++i)
    {
        s = curs;
        curs = curs->suiv;
        free(s);
    }
    free(l);
}

bool est_vide(LISTE* l)
{
    return l->taille == 0;
}