#include <stdio.h>
#include <assert.h>

#include "file.h"

int main()
{
    FIFO* f = file_vide();
    assert(est_file_vide(f));

    enfiler(f, 'f');
    enfiler(f, 'i');
    enfiler(f, 'l');
    enfiler(f, 'e');

    affiche_file(f);
    printf("Deux premiers elements : ");
    T prem = defiler(f);
    affiche_element(prem);
    enfiler(f, prem);
    printf(", ");
    T dem = defiler(f);
    affiche_element(dem);
    printf("\n");


    free_file(f);

    return 0;
}