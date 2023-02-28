#include <stdio.h>

//Affiche chaque chiffre d'un nombre sur une ligne différente

//Cette fonction affiche le dernier chiffre de n.
//Appelée récursivement sur n/10 avant le printf, elle affiche ce chiffre en
//remontant dans l'arbre l'appel, donc elle affiche les chiffres dans le bon ordre. 
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
    //L'appel se fait avant le printf pour que les chiffres soient dans le bon ordre.
    int chiffre = n % 10;
    affiche_chiffres(n / 10);
    printf("%d\n", chiffre);
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