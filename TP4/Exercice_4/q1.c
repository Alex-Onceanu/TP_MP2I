#include <stdio.h>
#include <stdbool.h>

bool ignore(char c)
{
    //Renvoie true si c est blanc, false sinon.
    if(c == ' ' || c == '\t' || c == '\n') return true;
    return false;
}

char scan_char()
{
    //Renvoie le premier charactere non blanc dans le terminal.
    char c;
    do {
        scanf("%c", &c);
    }while(ignore(c));
    return c;
}

int main()
{
    char test = scan_char();
    
    printf("Le premier char est \'%c\' !", test);
    
    return 0;
}