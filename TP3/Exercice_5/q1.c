#include <stdio.h>

#define LEN 7

void doubler_tableau(int tab[], int n)
{
    for(int i = 0; i < n; ++i)
    {
        tab[i] *= tab[i];
    }
}

int main()
{
    int tt[LEN] = { 3, 4, -7, 9, 76, 0, -1 };
    doubler_tableau(tt, LEN);

    for(int j = 0; j < LEN; ++j)
    {
        printf("%d\n", tt[j]);
    }
    return 0;
}