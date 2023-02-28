#include <stdio.h>

#define LEN 6

int main()
{
    float tab[LEN] = { 5, -3.6, 28, 9.2, 17, 0.02 };

    for(int i = 0; i < LEN; ++i)
    {
        printf("%f\n", tab[i]);
    }
    return 0;
}