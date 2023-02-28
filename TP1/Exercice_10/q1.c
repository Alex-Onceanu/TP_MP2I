/*Le programme demande à l'utilisateur un nombre entier,
puis affiche "Votre nombre vaut 0" s'il vaut 0, 
ou "Votre nombre ne vaut pas 0" sinon.*/

#include <stdio.h>

int main()
{
    int n;
    printf("Rentrez un nombre entier svp : ");
    scanf("%d", &n);

    if(n == 0)
    {
        printf("Votre nombre vaut 0\n");
    }
    else
    {
        printf("Votre nombre ne vaut pas 0\n");
    }

    return 0;
}