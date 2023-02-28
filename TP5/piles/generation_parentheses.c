#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pile.h"

char* generer_bp(int n)
{
    PILE* P = pile_vide();
    char* res = malloc(sizeof(char) * (2*n+1));
    empiler(P, ')');
    res[0] = '(';
    int i = 1;
    int N = n - 1;
    bool a;
    bool piece;

    while(N > 0)
    {
        a = rand() % 2;
        if(a == false || est_vide(P))
        {
            piece = rand() % 2;
            empiler(P, piece == true ? ')' : ']');
            res[i] = piece == true ? '(' : '[';
            --N;
        }
        else
        {
            res[i] = depiler(P);
        }
        ++i;
    }
    while(!est_vide(P))
    {
        res[i] = depiler(P);
        ++i;
    }

    res[2*n] = '\0';
    return res;
}

int main(int argc, char** argv)
{
    srand(time(NULL));

    if(argc != 2)
    {
        printf("argc == %d.\nNombre d'arguments invalide. Ce programme prend 1 entier pair k comme argument.\n", argc);
        return -1;
    }

    int k = atoi(argv[1]);

    if(k % 2 == 1)
    {
        printf("k == %d.\nUtilisation invalide. k doit etre pair.\n", k);
        return -1;
    }

    char* bp = generer_bp(k / 2);

    printf("%s\n", bp);

    return 0;
}