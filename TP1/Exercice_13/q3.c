#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randint(unsigned int maximum)
{
    if(maximum < 0) return 0;
    //Renvoie un entier aléatoire entre 0 et maximum (compris)
    return rand() % (maximum + 1);
}

int main()
{
    srand(time(NULL));

    printf("Nombre aléatoire !!\nVoici : %d\n\n", randint(99));

    return 0;
}