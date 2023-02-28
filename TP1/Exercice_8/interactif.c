#include <stdio.h>

int main()
{
    //On crée deux variables entières x et y sans les initialiser
    int x;
    int y;

    //On demande et on récupère x
    printf("Entrez x: ");
    scanf("%d", &x);

    //On demande et on récupère y
    printf("Entrez y: ");
    scanf("%d", &y);

    //On affiche x, y et leur somme
    printf("x vaut %d, y vaut %d, la somme vaut %d\n", x, y, x + y);

    return 0;
}