#include <stdio.h>

int main()
{
    int n;
    printf("Veuillez rentrer un nombre entier : ");
    scanf("%d", &n);

    //booléens, ces variables sont des conditions à vérifier dans les if
    int gou = (n % 3 == 0);
    int ba = (n % 5 == 0);

    /*Algo naïf : on teste chaque possibilté
    Soit 15 | n, soit 3 | n soit 5 | n, soit aucun des 3
    Autre variante d'algo, écrire "gou" ou "ba" dans un string à afficher
    Ce qui ne recquiert que 2 if, mais avec les connaissances du cours la version naïve est plus logique.*/
    if(gou && ba)
    {
        printf("gouba");
    }
    else if(gou)
    {
        printf("gou");
    }
    else if(ba)
    {
        printf("ba");
    }
    else
    {
        printf("%d", n);
    }
    printf("\n");

    return 0;
}