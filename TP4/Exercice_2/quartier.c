#include <stdio.h>
#include <stdlib.h>

#include "utility.h"
#include "quartier.h"
#include "maison.h"

struct quartier{
    maison_p* maisons;
    int nb_maisons;
    int prix_moyen_m2;
};

quartier_p quartier_init(maison_p __maisons[], int __nb_maisons, int __prix)
{
    quartier_p resultat = malloc(sizeof(quartier_t));    
    resultat->nb_maisons = __nb_maisons;
    resultat->prix_moyen_m2 = __prix;
    resultat->maisons = maison_init_array(__nb_maisons);

    if(__maisons != NULL)
    {
        for(int i = 0; i < __nb_maisons; ++i)
        {
            resultat->maisons[i] = __maisons[i];
        }
    }

    return resultat;
}

quartier_p quartier_init_aleatoire()
{
    quartier_p resultat = malloc(sizeof(quartier_t));

    resultat->nb_maisons = RandInt(2, 10);
    resultat->prix_moyen_m2 = RandInt(1000, 14000);
    resultat->maisons = maison_init_array(resultat->nb_maisons);

    for(int i = 0; i < resultat->nb_maisons; ++i)
    {
        resultat->maisons[i] = maison_init_aleatoire();
    }

    return resultat;
}

quartier_p* quartier_init_array(int length)
{
    quartier_p* resultat = malloc(sizeof(quartier_p) * length);
    return resultat;
}

void quartier_free(quartier_p this)
{
    if(this == NULL) return;

    for(int i = 1; i < this->nb_maisons; ++i)
    {
        maison_free(this->maisons[i]);
    }
    free(this);
}

void quartier_free_array(quartier_p* this)
{
    free(this);
}

int quartier_get_prix_moyen(quartier_p q)
{
    if(q != NULL) return q->prix_moyen_m2;
}

int quartier_cout_total(quartier_p q)
{
    int surface_totale = 0;
    for(int m = 0; m < q->nb_maisons; ++m)
    {
        surface_totale += maison_get_surface(q->maisons[m]);
    }
    return surface_totale * (q->prix_moyen_m2);
}

void quartier_affiche(quartier_p q)
{
    printf("Cout moyen du m2 ici : %d\n", q->prix_moyen_m2);
    for(int m = 0; m < q->nb_maisons; ++m)
    {
        printf("%deme ", m);
        maison_affiche(q->maisons[m]);
    }
}