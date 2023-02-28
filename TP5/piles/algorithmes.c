#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "pile.h"

bool bien_parenthese(char* mot, int n)
{
    PILE* p = pile_vide();
    T lettre = mot[0];
    for(int i = 0; i < n; ++i)
    {
        lettre = mot[i];
        if(lettre == '(' || lettre == '[')
        {
            empiler(p, lettre);
        }
        else if(lettre == ')')
        {
            if(est_vide(p)) return false;
            if(depiler(p) != '(') return false;
        }
        else if(lettre == ']')
        {
            if(est_vide(p)) return false;
            if(depiler(p) != '[') return false;
        }
    }
    bool reponse = est_vide(p);
    free_pile(p);

    return reponse;
}