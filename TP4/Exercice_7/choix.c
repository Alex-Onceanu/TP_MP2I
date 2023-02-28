#include <stdio.h>
#include <stdlib.h>

#include "utility.h"
#include "choix.h"


struct choix{
    char* texte;
    int page_suivante;
};

choix_p generer_choix(FILE* f)
{
    choix_p resultat = malloc(sizeof(choix_t));
    resultat->texte = malloc(sizeof(char) * MAX_LENGTH);

    fscan_ligne(f, resultat->texte);
    fscanf(f, "%d", &(resultat->page_suivante));
    //Pour se debarrasser du \n
    fseek(f, 1, SEEK_CUR);

    return resultat;
}

choix_p* choix_init_array(int length)
{
    choix_p* res = malloc(sizeof(choix_p) * length);
    return res;
}

void choix_afficher(choix_p this)
{
    printf("%s\n", this->texte);
}

char* choix_get_texte(choix_p this)
{
    return this->texte;
}

int choix_get_page_suivante(choix_p this)
{
    return this->page_suivante;
}

void free_choix(choix_p this)
{
    free(this->texte);
    free(this);
}