/*
Ce programme affiche "cas A", "cas B" ou "cas C" en fonction du nombre rentré par l'utilisateur.
*/

#include <stdio.h>

int main()
{
    int n;
    printf("Veuillez rentrer un nombre entier : ");
    scanf("%d",&n);

    if(n < -0.33)
    {
        printf("cas A\n");
    }
    else if(n <= 7.89)
    {
        printf("cas B\n");
    }
    else
    {
        printf("cas C\n");
    }
    
    return 0;
}