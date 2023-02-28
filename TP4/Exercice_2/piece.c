#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "utility.h"
#include "piece.h"

struct piece{
    int longueur;
    int largeur;
    int nb_fenetres;

    bool possede_chauffage;

    char* nom;
};

piece_p piece_init(int lng, int lrg, int nb_f, bool chauffage, char* __nom)
{
    piece_p resultat = malloc(sizeof(piece_t));

    resultat->longueur = lng;
    resultat->largeur = lrg;
    resultat->nb_fenetres = nb_f;
    resultat->possede_chauffage = chauffage;
    resultat->nom = malloc(sizeof(char) * strlen(__nom));
    
    strcpy(resultat->nom, __nom);

    return resultat;
}

piece_p piece_init_aleatoire()
{
    char* noms[8] = { "Salon", "Chambre", "Chambre", "Chambre", 
        "Salle de bain", "Cuisine", "Garage", "Grenier" };

    return piece_init(RandInt(1,15), RandInt(1, 15), RandInt(0, 5),
                 RandInt(0, 1), noms[RandInt(0, 7)]);
}

piece_p* piece_init_array(int length)
{
    piece_p* resultat = malloc(sizeof(piece_p) * length);
    return resultat;
}

void piece_free_array(piece_p* this)
{
    free(this);
}

void piece_free(piece_p this)
{
    if(this == NULL) return;
    free(this->nom);
    free(this);
}

void piece_affiche(piece_p piece)
{
    if(piece == NULL) return;

    printf("piece \"%s\" : mesure %dx%d, possede %d fenetres",
        piece->nom, piece->longueur, piece->largeur, piece->nb_fenetres);
    
    if(piece->possede_chauffage)
    {
        printf(" et est chauffee");
    }
    printf(".\n");
}

int piece_get_surface(piece_p p)
{
    if(p == NULL) return 0;
    return p->longueur * p->largeur;
}

int piece_get_nb_fenetres(piece_p p)
{
    if(p == NULL) return 0;
    return p->nb_fenetres;
}

bool piece_possede_chauffage(piece_p p)
{
    if(p == NULL) return false;
    return p->possede_chauffage;
}