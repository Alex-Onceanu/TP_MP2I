#include <stdio.h>

int main()
{
    //On définit les variables
    int x = 3;
    float y = 0.25f;

    //somme_f est décimal, somme_i entier relatif
    float somme_f = x + y;
    int somme_i = x + y;

    //On affiche les 4 variables
    printf("x = %d\ny = %f\nsomme_f = %f\nsomme_i = %d\n", x, y, somme_f, somme_i);

    return 0;
}