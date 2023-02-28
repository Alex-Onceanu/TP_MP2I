#include <stdio.h>
#include <stdbool.h>

#include "utility.h"


bool fscan_ligne(FILE* f, char* str)
{
    int i = 0;
    char c;
    bool eof = false;
    while(c != '\n')
    {
        eof = (fscanf(f, "%c", &c) == EOF) || eof;
        str[i] = c;
        i++;
        if(eof) break;
    }
    str[i - 1] = '\0';
    return eof;
}

int meilleur_scanf(char* message, int borne_min, int borne_max)
{
    if(borne_min > borne_max)
    {
        //Parce qu'on sait jamais...
        int tmp = borne_max;
        borne_max = borne_min;
        borne_min = tmp;
    }

    printf("%s", message);
    fflush(stdout);

    int resultat;

    bool should_continue = (scanf("%d", &resultat) == 0);
    while(getc(stdin) != '\n');

    while(should_continue || (resultat < borne_min) || (resultat > borne_max))
    {
        printf("Merci d'entrer un entier compris entre %d et %d.\n",
                borne_min, borne_max);
        printf("%s", message);

        should_continue = (scanf("%d", &resultat) == 0);
        while(getc(stdin) != '\n');
    }

    return resultat;
}