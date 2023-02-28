#include <stdio.h>
#include <stdbool.h>

#include "pile.h"

int main()
{
    PILE* p1 = pile_vide();
    bool vide = est_vide(p1);

    empiler(p1, 'e');
    empiler(p1, 'l');
    empiler(p1, 'i');
    empiler(p1, 'a');

    depiler(p1);
    empiler(p1, 'p');

    affiche_pile(p1);

    free_pile(p1);

    return 0;
}