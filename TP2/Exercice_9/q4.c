#include <stdio.h>
#include <assert.h>

//Affiche n fois le caractère 'O' puis un '\n'
void plein_de_O(int n)
{
    if(n == 0)
    {
        printf("\n");
        return;
    }
    printf("O");
    return plein_de_O(n - 1);
}

int main()
{
    //On prend en entrée un entier n positif
    int n;
    printf("n : ");
    scanf("%d", &n);
    assert(n >= 0);
    
    plein_de_O(n);
    return 0;
}