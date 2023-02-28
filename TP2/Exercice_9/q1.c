#include <stdio.h>
#include <assert.h>

//affiche les n premiers entiers, n étant un entier positif demandé à l'utilisateur.

void affiche_premiers(int n)
{
    if(n < 0) return;
    affiche_premiers(n - 1);
    printf("%d\n", n);
}

int main()
{
    int n;
    printf("n : ");
    scanf("%d", &n);
    assert(n >= 0);

    affiche_premiers(n);

    return 0;
}