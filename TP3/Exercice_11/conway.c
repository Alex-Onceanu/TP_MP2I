/*
/!\ Le programme est une boucle infinie, il faut absolument faire ^C pour 
qu'il s'arrete. (ainsi on peut l'arreter a tout moment ou le laisser tourner)

/!\ Si vous avez un petit écran, il faut peut être dézoomer pour voir toute la map
Ou alors enlever quelques lignes de la matrice initiale

/!\ Ce programme ne marche que sur linux, a cause de system("clear")
(il aurait fallu faire system("cls") sur windows)

//_______________________description_________________________________

Le jeu de la vie est un jeu qui se joue a 0 joueurs (donc le jeu se joue tout seul)
Il se base sur un quadrillage de cellules, ou chaque cellule est soit
vivante (X) soit morte (.)
On associe ces cellules a des etres vivants unicellulaires (d'ou le nom)

Toutes les 0,48s, une nouvelle generation de cellules nait en fonction de la precedente.
Donc on admire ces formes de vie evoluer en de differentes formes
Certaines formes vont etre "stables", et ne vont pas changer de forme
D'autres seront "periodiques", etc

____________________regles du jeu______________________________________

Pour chaque cellule :
Si elle est morte mais qu'elle a exactement 3 cellules voisines vivantes, elle "nait"
    (donc devient vivante)
Si elle est vivante et qu'elle a 2 ou 3 cellules voisines vivantes, elle le reste
    (sinon elle meurt)

Il existe toute une science derriere ce jeu, avec des chercheurs cherchant
de nouvelles formes amusantes
Par exemple tout en bas de l'etat initial actuellement implemente, il y a un "canon"
qui va lancer des "gliders" periodiquement qui planent vers le bas..

*///_______________________initialisation_______________________________

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>

//Par securite, il faut toujours indiquer la taille de la map
//Longueur = nb de cases en horizontal, largeur en vertical
#define LONGUEUR 64
#define LARGEUR 46

//Vous pouvez modifier cette macro pour differentes fins (ou non-fins)
#define ETAT_INITIAL "\
................................................................\
................................................................\
.....................XXX...XXX..................................\
................................................................\
...................X....X.X....X................................\
...................X....X.X....X................................\
...................X....X.X....X................................\
.....................XXX...XXX..................................\
................................................................\
.....................XXX...XXX..................................\
...................X....X.X....X................................\
...................X....X.X....X................................\
...................X....X.X....X................................\
................................................................\
.....................XXX...XXX..................................\
................................................................\
................................................................\
................................................................\
................................................................\
.......X........................................................\
......XXX.......................................................\
.......X....................................X.X.................\
........................................X.X..X..................\
.........................................X...X..................\
.........................................X.....X................\
................................................................\
................................................................\
................................................................\
................................................................\
................................................................\
................................................................\
........................X.......................................\
......................X.X.......................................\
............XX......XX............XX............................\
...........X...X....XX............XX............................\
XX........X.....X...XX..........................................\
XX........X...X.XX....X.X.......................................\
..........X.....X.......X.......................................\
...........X...X................................................\
............XX..................................................\
................................................................\
................................................................\
................................................................\
................................................................\
XX............................................................XX\
XX............................................................XX"

//matrice est un tableau de unsigned long int
//Chaque element du tableau correspond a une ligne, ou chaque bit est une cellule
uint64_t matrice[LARGEUR];
//On a besoin d'une copie de la matrice principale pour faire les mises a jour
uint64_t ancienne_matrice[LARGEUR];


//_______________________fonctions auxiliaires________________________________________

int get_cellule(uint64_t mtrx[LARGEUR], int ligne, int index)
{
    //Renvoie l'etat de la cellule de coordonnees (index, ligne)
    //Ne peut renvoyer que 0 ou 1
    assert(ligne >= 0 && ligne < LARGEUR);
    return (mtrx[ligne] >> index) & 1;
}

void set_cellule(int ligne, uint32_t index)
{
    //La cellule de coordonnees (index, ligne) de matrice prend la valeur 1
    assert(ligne >= 0 && ligne < LARGEUR);
    matrice[ligne] |= ((unsigned long int)(1) << index);
}

void unset_cellule(int ligne, uint32_t index)
{
    //La cellule de coordonnees (index, ligne) de matrice prend la valeur 0
    assert(ligne >= 0 && ligne < LARGEUR);
    matrice[ligne] &= (~((unsigned long int)(1) << index)); 
}

void CreerMatrice(char* initial, int len)
{
    //A partir de la grosse macro en format char* avec des X et des .
    //Remplit la matrice avec des lignes de uint64_t
    //Pour chaque ligne, chaque bit represente une cellule
    assert(len == LONGUEUR * LARGEUR);

    char cellule;
    int ligne = 0;
    for(int i = len - 1; i >= 0; --i)
    {
        cellule = initial[i];
        ligne = i / LONGUEUR;
        matrice[ligne] += cellule == 'X' ? 1 : 0;

        //Ne pas tout decaler pour la derniere valeur de chaque ligne
        if((i % LONGUEUR) == 0) continue;

        matrice[ligne] = matrice[ligne] << 1;
    }
}

void copier_matrice(uint64_t source[LARGEUR], uint64_t dest[LARGEUR], int taille)
{
    //dest <- source
    for(int i = 0; i < taille; ++i)
    {
        dest[i] = source[i];
    }
}

void afficher_matrice()
{
    //Uniquement pour les tests
    for(int y = 0; y < LARGEUR; ++y)
    {
        printf("%ld\n", matrice[y]);
    }
}

int nb_voisins(uint64_t mtrx[LARGEUR], int ligne, int index)
{
    //Renvoie le nombre de voisins vivants de la case de coord. (index, ligne)
    assert(ligne >= 0 && ligne < LARGEUR);

    int somme = 0;

    for(int y = ligne - 1; y <= ligne + 1; ++y)
    {
        for(int x = index - 1; x <= index + 1; ++x)
        {
            if(x == index && y == ligne) continue;
            if(x < 0 || x >= LONGUEUR) continue;
            if(y < 0 || y >= LARGEUR) continue;

            somme += get_cellule(mtrx, y, x);
        }
    }

    return somme;
}


//________________________________Fonctions principales_________________________

void Update()
{
    //On passe a la generation suivante : toutes les cellules sont mises a jour
    //cf regles du jeu tout en haut du fichier code
    
    //On a besoin d'une copie de la matrice principale :
    //Pour ne pas modifier en temps reel la matrice qui sert de comparaison
    copier_matrice(matrice, ancienne_matrice, LARGEUR);
    int voisins = 0;

    //Pour chaque cellule de coordonnees (x, y),
    for(int y = 0; y < LARGEUR; ++y)
    {
        for(int x = 0; x < LONGUEUR; ++x)
        {
            //On calcule son nombre de voisins vivants et on la met a jour
            voisins = nb_voisins(ancienne_matrice, y, x);

            if(get_cellule(ancienne_matrice, y, x) == 0)
            {
                if(voisins == 3)
                {
                    set_cellule(y, x);
                }
            }
            else
            {
                if(voisins < 2 || voisins > 3)
                {
                    unset_cellule(y, x);
                }
            }
        }
    }
}

void Draw()
{
    //Affiche toutes les cases du jeu selon l'etat actuel de matrice
    char crayon;
    for(int y = 0; y < LARGEUR; ++y)
    {
        uint64_t ligne = matrice[y];
        for(int cellule = 0; cellule < LONGUEUR; ++cellule)
        {
            crayon = ligne % 2 == 1 ? 'X' : '.';
            printf("%2c", crayon);
            ligne = ligne >> 1;
        }
        printf("\n");
    }
}

int main()
{
    system("clear");
    //On initialise la matrice principale en fonction de l'etat initial
    CreerMatrice(ETAT_INITIAL, LONGUEUR * LARGEUR);

    while(1)
    {
        //Boucle principale du jeu
        //Le programme n'est pas interactif, la boucle est infinie...

        //A chaque frame, on efface la frame precedente, affiche la frame actuelle
        //Puis on met a jour la matrice pour obtenir la frame suivante
	printf("\033[0;0H");
        Draw();
        //On attend quelques ms entre chaque frame, ici 1frame/0,48s
        usleep(480000);
        Update();
    }

    //Ce return ne sera jamais atteint :( (quel developpeur cruel..)
    return 0;
}