#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initialise_random(int t[], int n, int a, int b)
{
    for(int i = 0; i < n; ++i)
    {
        t[i] = rand() % (b - a) + a;
    }
}

int main()
{
    srand(time(NULL));

    int tab[5];
    initialise_random(tab, 5, 6, 12);

    for(int j = 0; j < 5; ++j)
    {
        printf("%d\n", tab[j]);
    }

    return 0;
}