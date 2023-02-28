#include <stdio.h>
#include <assert.h>

//Affiche les n premiers entiers, n entier positif demandé à l'utilisateur
int main()
{   
    int n;
    printf("n : ");
    scanf("%d", &n);
    assert(n > 0);

    for(int i = 1; i <= n; i++)
    {
        printf("%d\n", i);
    }

    return 0;
}