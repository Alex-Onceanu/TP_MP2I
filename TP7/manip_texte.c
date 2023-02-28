#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "hashtable.h"

#define M 100

void test()
{
    DICT* d = dict_vide(M);

    char* x = malloc(14 * sizeof(char));
    strcpy(x, "hello world !");
    inserer(d, x, 2);

    char* x2 = malloc(16 * sizeof(char));
    strcpy(x2, "starlighto anya");
    inserer(d, x2, 1);

    char* x3 = malloc(16 * sizeof(char));
    strcpy(x3, "camelcamelcamel");
    inserer(d, x3, 4);

    char* verif = trouver_max(d);

    assert(strcmp(verif, "camelcamelcamel") == 0);

    printf("Test passed.\n");

    free(verif);
    free_keys(d);
    free_dict(d);
}

int main(int argc, char** argv)
{
    test();

#if QUESTION_BONUS
    if(argc == 4)
    {
        mots_plus_frequents(argv[1], atoi(argv[2]), atoi(argv[3]));
    }
    else if(argc == 3)
    {
        mots_plus_frequents(argv[1], atoi(argv[2]), 10);
    }
    else
    {
        printf("Mauvaise utilisation du programme. Arguments : ./a.out fn K n_mots\n");
    }
#else
    if(argc == 4)
    {
        mot_plus_frequent(argv[1], atoi(argv[2]), atoi(argv[3]));
    }
    else if(argc == 3)
    {
        mot_plus_frequent(argv[1], atoi(argv[2]), 15319);
    }
    else
    {
        printf("Mauvaise utilisation du programme. Arguments : ./a.out fn K m\n");
    }
#endif

    return 0;
}