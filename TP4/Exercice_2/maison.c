#include <stdio.h>
#include <stdlib.h>

#include "maison.h"
#include "etage.h"
#include "utility.h"

struct maison{
    etage_p* etages;
    int nb_etages;
};

maison_p maison_init(etage_p __etages[], int __nb_etages)
{
    maison_p resultat = malloc(sizeof(maison_t));    
    resultat->nb_etages = __nb_etages;
    resultat->etages = etage_init_array(__nb_etages);

    if(__etages != NULL)
    {
        for(int i = 0; i < __nb_etages; ++i)
        {
            resultat->etages[i] = __etages[i];
        }
    }

    return resultat;
}

maison_p maison_init_aleatoire()
{
    maison_p resultat = malloc(sizeof(maison_t));    

    resultat->nb_etages = RandInt(1,3);
    resultat->etages = etage_init_array(resultat->nb_etages);
    
    for(int i = 0; i < resultat->nb_etages; ++i)
    {
        resultat->etages[i] = etage_init_aleatoire();
    }

    return resultat;
}

void maison_free(maison_p this)
{
    if(this == NULL) return;

    for(int i = 1; i < this->nb_etages; ++i)
    {
        etage_free(this->etages[i]);
    }
    free(this);
}

maison_p* maison_init_array(int length)
{
    maison_p* resultat = malloc(sizeof(maison_p) * length);
    return resultat;
}

void maison_free_array(maison_p* this)
{
    free(this);
}

void maison_affiche(maison_p maison)
{
    if(maison == NULL) return;

    printf("maison :\n\t");
    for(int e = 0; e < maison->nb_etages; ++e)
    {
        etage_affiche(maison->etages[e]);
        printf("\n\t");
    }
    printf("\n");
}

int maison_get_nb_fenetres(maison_p m)
{
    if(m == NULL) return 0;

    int compt = 0;
    for(int e = 0; e < m->nb_etages; ++e)
    {
        compt += etage_get_nb_fenetres(m->etages[e]);
    }
    return compt;
}

int maison_get_surface(maison_p m)
{
    if(m == NULL) return 0;
    
    int surf = 0;
    for(int e = 0; e < m->nb_etages; ++e)
    {
        surf += etage_get_surface(m->etages[e]);
    }
    return surf;
}

int maison_get_nb_chauffages(maison_p m)
{
    if(m == NULL) return 0;

    int compt = 0;
    for(int e = 0; e < m->nb_etages; ++e)
    {
        compt += etage_get_nb_chauffages(m->etages[e]);
    }
    return compt;
}

maison_p maison_empiler(maison_p m1, maison_p m2)
{
    if(m1 == NULL) return m2;
    if(m2 == NULL) return m1;

    int nb_etages_empiles = m1->nb_etages + m2->nb_etages;
    etage_p* etages_empiles = etage_init_array(nb_etages_empiles);

    for(int i1 = 0; i1 < m1->nb_etages; ++i1)
    {
        etages_empiles[i1] = m1->etages[i1];
    }
    for(int i2 = 0; i2 < m2->nb_etages; ++i2)
    {
        etages_empiles[i2 + m1->nb_etages] = m2->etages[i2];
    }
    
    return maison_init(etages_empiles, nb_etages_empiles);
}
