#include <stdio.h>


int main()
{
    int n = 0;
    
    //On demande à l'utilisateur une valeur pour n jusqu'à ce qu'elle soit valide.
    do
    {
        printf("Veuillez rentrer un nombre : ");
        scanf("%d", &n);
        //Pour pas que le programme plante chez les farceurs
        while(getchar() != '\n');
    } while(n < 0);

    printf("Votre nombre s'ecrit : %c\n", n);

    return 0;
}