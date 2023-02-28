#include <stdio.h>

/*
La seule différence avec la réponse précédente est que l'appel 
récursif se fait après le printf, cela inverse l'ordre d'affichage des chiffres.

Cette fonction affiche le dernier chiffre de n.
Appelée récursivement sur n/10 après le printf, elle affiche ce chiffre en
descendant dans l'arbre l'appel, donc elle affiche les chiffres dans l'ordre inverse. 
*/
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
    //L'appel se fait après le printf pour que les chiffres soient dans l'ordre inverse.
    int chiffre = n % 10;
    printf("%d\n", chiffre);
    affiche_chiffres(n / 10);
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