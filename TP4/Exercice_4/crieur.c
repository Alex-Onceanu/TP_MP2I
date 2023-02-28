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
    char c;
    do{
        c = scan_char();
        //-32 pour passer de minuscule a majuscule.
        c -= 32;
        printf("%c %c %c\n", c, c, c);
    }while(c != 'Z');

    return 0;
}


//le celebre programme du samedi matin.