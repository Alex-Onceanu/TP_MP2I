#include <stdio.h>
#include <stdlib.h>

#include "utility.h"
#include "ville.h"
#include "quartier.h"

//On assimile une ville a une matrice de quartiers.
struct ville{
    quartier_p** quartiers;
    int nb_lignes;
    int nb_colonnes;
};

ville_p ville_init(quartier_p** __quartiers, int __nb_lignes, int __nb_colonnes)
{
    ville_p resultat = malloc(sizeof(ville_t));    
    resultat->nb_lignes = __nb_lignes;
    resultat->nb_colonnes = __nb_colonnes;
    resultat->quartiers = malloc(sizeof(quartier_p*) * __nb_lignes);

    if(__quartiers != NULL)
    {
        for(int i = 0; i < __nb_lignes; ++i)
        {
            resultat->quartiers[i] = quartier_init_array(__nb_colonnes);
            if(__quartiers[i] == NULL) continue;

            for(int j = 0; j < __nb_colonnes; ++j)
            {
                resultat->quartiers[i][j] = __quartiers[i][j];
            }
        }
    }

    return resultat;
}

ville_p ville_init_aleatoire()
{
    ville_p resultat = malloc(sizeof(ville_t));    
    resultat->nb_lignes = RandInt(2, 5);
    resultat->nb_colonnes = RandInt(2, 5);
    resultat->quartiers = malloc(sizeof(quartier_p*) * resultat->nb_lignes);

    for(int i = 0; i < resultat->nb_lignes; ++i)
    {
        resultat->quartiers[i] = quartier_init_array(resultat->nb_colonnes);
        
        for(int j = 0; j < resultat->nb_colonnes; ++j)
        {
            resultat->quartiers[i][j] = quartier_init_aleatoire();
        }
    }

    return resultat;
}

ville_p* ville_init_array(int length)
{
    ville_p* resultat = malloc(sizeof(ville_p) * length);
    return resultat;
}

void ville_free(ville_p this)
{
    if(this == NULL) return;

    for(int y = 1; y < this->nb_lignes; ++y)
    {
        for(int x = 0; x < this->nb_colonnes; ++x)
        {
            quartier_free(this->quartiers[y][x]);
        }
        quartier_free_array(this->quartiers[y]);
    }
    free(this);
}

void ville_free_array(ville_p* this)
{
    free(this);
}

int ville_cout_total(ville_p v)
{
    int total = 0;
    for(int y = 0; y < v->nb_lignes; ++y)
    {
        for(int x = 0; x < v->nb_colonnes; ++x)
        {
            total += quartier_cout_total(v->quartiers[y][x]);
        }
    }
    return total;
}

void ville_affiche_prix_moyen(ville_p v)
{
    int i = 0;
    for(int y = 0; y < v->nb_lignes; ++y)
    {
        for(int x = 0; x < v->nb_colonnes; ++x)
        {
            printf("%3d : %5d$/m2", i, quartier_get_prix_moyen(v->quartiers[y][x]));
            i++;
        }
        printf("\n");
    }
}

void ville_affiche(ville_p v)
{
    ville_affiche_prix_moyen(v);
    printf("\n");

    int i = 0;
    for(int y = 0; y < v->nb_lignes; ++y)
    {
        for(int x = 0; x < v->nb_colonnes; ++x)
        {
            printf("quartier %d : {\n", i);
            quartier_affiche(v->quartiers[y][x]);
            printf("\n}\n");
            i++;
        }
    }
}