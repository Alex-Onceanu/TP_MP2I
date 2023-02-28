#include <stdio.h>
#include <stdlib.h>

#include "utility.h"
#include "piece.h"
#include "etage.h"

struct etage{
    piece_p* pieces;
    int nb_pieces;
};

etage_p etage_init(piece_p __pieces[], int __nb_pieces)
{
    etage_p resultat = malloc(sizeof(etage_t));
     
    resultat->nb_pieces = __nb_pieces;
    resultat->pieces = piece_init_array(__nb_pieces);
    for(int i = 0; i < __nb_pieces; ++i)
    {
        resultat->pieces[i] = __pieces[i];
    }

    return resultat;
}

etage_p etage_init_aleatoire()
{
    etage_p resultat = malloc(sizeof(etage_t));

    resultat->nb_pieces = RandInt(1, 5);
    resultat->pieces = piece_init_array(resultat->nb_pieces);

    for(int i = 0; i < resultat->nb_pieces; ++i)
    {
        resultat->pieces[i] = piece_init_aleatoire();
    }
    return resultat;
}

void etage_free(etage_p this)
{
    if(this == NULL) return;

    for(int i = 1; i < this->nb_pieces; ++i)
    {
        piece_free(this->pieces[i]);
    }
    free(this);
}

etage_p* etage_init_array(int length)
{
    etage_p* resultat = malloc(sizeof(etage_p) * length);
    return resultat;
}

void etage_free_array(etage_p* this)
{
    free(this);
}

int etage_get_nb_fenetres(etage_p e)
{
    if(e == NULL) return 0;

    int compt = 0;
    for(int p = 0; p < e->nb_pieces; ++p)
    {
        compt += piece_get_nb_fenetres(e->pieces[p]);
    }
    return compt;
}

int etage_get_surface(etage_p e)
{
    if(e == NULL) return 0;

    int surf = 0;
    for(int p = 0; p < e->nb_pieces; ++p)
    {
        surf += piece_get_surface(e->pieces[p]);
    }
    return surf;
}

int etage_get_nb_chauffages(etage_p e)
{
    if(e == NULL) return 0;

    int compt = 0;
    bool chauffage;
    for(int p = 0; p < e->nb_pieces; ++p)
    {
        chauffage = piece_possede_chauffage(e->pieces[p]);
        compt += chauffage ? 1 : 0;
        //J'aurais pref faire compt += int(chauffage)
        //Mais gcc n'a pas trop aimé
    }
    return compt;
}

void etage_affiche(etage_p etage)
{
    if(etage == NULL) return;

    printf("etage :\n\t");
    for(int p = 0; p < etage->nb_pieces; ++p)
    {
        piece_affiche(etage->pieces[p]);
        printf("\t");
    }
}