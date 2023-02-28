#include <stdio.h>

/*
Demande un nombre entier à l'utilisateur, puis 
affiche autant de 'O' par ligne que chaque chiffre du nombre. (avec un - pour les négatifs)

...pour n = 92729 on a un E
OOOOOOOOO
OO
OOOOOOO
OO
OOOOOOOOO
*/

//Affiche n fois le caractère 'O' puis un '\n'
void plein_de_O(int n)
{
    if(n == 0)
    {
        printf("\n");
        return;
    }
    printf("O");
    return plein_de_O(n - 1);
}

//Même fonction que précédemment, mais en appelant plein_de_O au lieu de printf.
void affiche_chiffres(int n)
{
    //Cas de base : la fonction s'arrête une fois qu'il n'y a plus de chiffres.
    if(n == 0) return;
    //Si n est négatif on le rend positif et on affiche un '-'
    if(n < 0)
    {
        n = -n;
        printf("-\n");
    }

    //n % 10 est le dernier chiffre de n.
    //On veut afficher autant de '0' grâce à plein_de_O
    int chiffre = n % 10;
    affiche_chiffres(n / 10);
    plein_de_O(chiffre);
}

int main()
{
    //On prend en entrée un entier n quelconque
    int n;
    printf("n : ");
    scanf("%d", &n);
    
    affiche_chiffres(n);

    return 0;
}