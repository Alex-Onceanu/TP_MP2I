#include <stdio.h>
#include <assert.h>

int factorielle(int n)
{
    //Calcule n! = n*(n-1)*(n-2)*...*1 pour n positif ou nul
    assert(n >= 0);
    if(n == 0) return 1;
    return n * factorielle(n-1);
}

int main()
{
    int n;
    scanf("%d", &n);

    printf("%d\n", factorielle(n));

    return 0;
}