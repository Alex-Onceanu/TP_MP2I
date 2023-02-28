#include <stdio.h>
#include <stdlib.h>

#include "livre.h"
#include "page.h"

struct livre{
    int n_pages;
    page_p* pages;
};

livre_p generer_livre(char* filename)
{
    FILE* fichier = fopen(filename, "r");
    if(fichier == NULL) return NULL;

    livre_p resultat = malloc(sizeof(livre_t));

    fscanf(fichier, "%d", &(resultat->n_pages));
    //Pour se debarrasser du \n
    fseek(fichier, 1, SEEK_CUR);

    resultat->pages = page_init_array(resultat->n_pages);

    for(int i = 0; i < resultat->n_pages; ++i)
    {
        resultat->pages[i] = generer_page(fichier);
    }

    fclose(fichier);

    return resultat;
}

void LDVELH(livre_p bouquin)
{
    int page_suivante = 0;
    while(page_suivante != -1)
    {
        page_suivante = page_afficher(bouquin->pages[page_suivante]);
    }
}

int livre_get_n_pages(livre_p this)
{
    return this->n_pages;
}

page_p* livre_get_pages(livre_p this)
{
    return this->pages;
}

void free_livre(livre_p this)
{
    for(int i = 0; i < this->n_pages; ++i)
    {
        free_page(this->pages[i]);
    }
    free(this);
}