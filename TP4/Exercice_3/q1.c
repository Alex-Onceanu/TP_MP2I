#include <stdio.h>
#include <stdlib.h>


void scan_ligne(char* str)
{
    int i = 0;
    char c;
    while(c != '\n')
    {
        scanf("%c", &c);
        str[i++] = c;
    }
    str[i - 1] = '\0';
}

int main()
{
    char ss[200] = "";
    scan_ligne(ss);
    printf("Vous avez dit %s !!\n", ss);
    return 0;
}