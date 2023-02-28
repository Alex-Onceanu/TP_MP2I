#include <stdlib.h>

#include "utility.h"


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
