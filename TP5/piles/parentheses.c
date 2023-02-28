#include <stdio.h>
#include <stdbool.h>

#include "algorithmes.h"

#define MAX_N 10000

int main()
{
    char mot[MAX_N] = "";
    int lus = scanf("%s", mot);

    bool resultat = bien_parenthese(mot, MAX_N);

    printf("Resultat : %s\n", resultat == true ? "true" : "false");


    return 0;
}