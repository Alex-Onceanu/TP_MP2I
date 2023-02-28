/*
Le programme affiche la médiane de trois nombres rentrés par l'utilisateur.
*/

#include <stdio.h>

int main()
{
    int a;
    int b;
    int c;

    printf("Veuillez rentrer un premier nombre : ");
    scanf("%d",&a);
    printf("Veuillez rentrer un deuxième nombre : ");
    scanf("%d",&b);
    printf("Veuillez rentrer un troisième nombre : ");
    scanf("%d",&c);

    //Il y a que trois possibilités, deux cas par possibilité de médiane
    //...Donc 6 possibilités, qu'on teste avec des if 
    if((a < b && b < c) || (a > b && b > c))
    {
        printf("La médiane est %d",b);
    }
    else if((b < a && a < c) || (b > a && a > c))
    {
        printf("La médiane est %d",a);
    }
    else if((a < c && c < b) || (a > c && c > b))
    {
        printf("La médiane est %d",c);
    }
    //Il y a erreur si aucun des cas n'est rempli.
    else
    {
        printf("\nIl y a erreur, merci de rentrer des entiers la prochaine fois.");
    }

    printf("\n");
    return 0;
}