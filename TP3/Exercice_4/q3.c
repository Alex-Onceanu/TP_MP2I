#include <stdio.h>

#define MAX_LEN 100000

void complete_tableau(int tab[], int n)
{
    for(int i = 0; i < n; ++i)
    {
        tab[i] = i*i;
    }
}

int main()
{
    //On initialise le tableau local, de taille maximale MAX_LEN
    int tab[MAX_LEN];
    //Mais on n'en utilisera qu'une partie [| 0, n |]
    int n = 0;
    
    //On demande à l'utilisateur une valeur pour n jusqu'à ce qu'elle soit valide.
    do
    {
        printf("Quelle taille de tableau ?\n");
        scanf("%d", &n);
        //Pour pas que le programme plante chez les farceurs
        while(getchar() != '\n');
    } while(n > MAX_LEN || n <= 0);

    complete_tableau(tab, n);

    //On affiche le tableau créé.
    for(int j = 0; j < n; ++j)
    {
        printf("%d\n", tab[j]);
    }

    return 0;
}