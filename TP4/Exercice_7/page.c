#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utility.h"
#include "page.h"
#include "choix.h"


struct page
{
    char* texte;
    int n_choix;
    //Tableau de pointeurs vers des choix.
    choix_p* choix;
};

page_p generer_page(FILE* f)
{
    page_p resultat = malloc(sizeof(page_t));
    resultat->texte = malloc(sizeof(char) * MAX_LENGTH);
    resultat->n_choix = 0;

    fscanf(f, "%d", &(resultat->n_choix));
    //Pour se debarrasser du \n
    fseek(f, 1, SEEK_CUR);

    resultat->choix = choix_init_array(resultat->n_choix);
    fscan_ligne(f, resultat->texte);

    for(int i = 0; i < resultat->n_choix; ++i)
    {
        resultat->choix[i] = generer_choix(f);
    }

    return resultat;
}

page_p* page_init_array(int length)
{
    page_p* res = malloc(sizeof(page_p) * length);
    return res;
}


int page_afficher(page_p this)
{
    printf("%s\n", this->texte);

    if(this->n_choix == 0) return -1;

    for(int i = 0; i < this->n_choix; ++i)
    {
        printf("\t%d. ", i + 1);
        choix_afficher(this->choix[i]);
    }

    int id_choisi = meilleur_scanf("Votre choix : ", 1, this->n_choix);
    printf("\n");

    return choix_get_page_suivante((this->choix[id_choisi - 1]));
}


char* page_get_texte(page_p this)
{
    return this->texte;
}

int page_get_n_choix(struct page * this)
{
    return this->n_choix;
}

choix_p* page_get_choix(page_p this)
{
    return this->choix;
}

void free_page(page_p this)
{
    free(this->texte);
    for(int i = 0; i < this->n_choix; ++i)
    {
        free_choix(this->choix[i]);
    }
    free(this);
}