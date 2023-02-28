#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

int RandInt(int borne_min, int borne_max)
{
    //Renvoie un entier aleatoire de l'intervalle [| borne_min, borne_max |]
    if(borne_min > borne_max)
    {
        int tmp = borne_max;
        borne_max = borne_min;
        borne_min = tmp;
    }
    return (rand() % (1 + borne_max - borne_min)) + borne_min;
}

void affiche()
{
    char c = RandInt(97, 122);
    printf("%c\n", c);
    fflush(stdout);
}


int main()
{
    srand(time(NULL));

    bool should_stop = false;
    
    while(!should_stop)
    {
        affiche();
        usleep(250000);
        should_stop = (RandInt(1, 20) == 1);
    }

    return 0;
}