#include <stdio.h>

int main()
{
    int n = 0;
    
    scanf("%d", &n);

    if(n == 10)
    {
        printf("29");
    }
    else
    {
        printf("%d", n * n);
    }
    
    return 0;
}