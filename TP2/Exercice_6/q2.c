/*
_|_
___|_
_____|_
_______|_
_________|_
___________|_
_____________|_
_______________|_
_________________|_
*/

#include <stdio.h>
#include <assert.h>

void palier_escalier(int i)
{
    //Affiche la i-ème ligne de l'escalier
    for(int j = 0; j <= 2*i; j++)
    {
        printf("_");
    }
    //J'ai préféré utiliser des '_' et ajouter un '_' après le '|' pour que ce soit + joli.
    printf("|_\n");
}

//Dessine un escalier à n marches, n entier positif rentré par l'utilisateur
int main()
{
    int n;
    printf("n : ");
    scanf("%d", &n);
    assert(n >= 0);

    for(int etage = 0; etage < n; etage++)
    {
        palier_escalier(etage);
    }
    
    return 0;
}