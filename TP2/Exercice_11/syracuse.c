#include <stdio.h>
#include <time.h>

//Calcule le terme suivant de la suite de syracuse
long int suivant(long int x)
{
    //On suppose que x est Un, on utilise donc x pour renvoyer Un+1
    //On vérifie si x est pair ou impair, on suit la définition.
    if(x % 2 == 0)
    {
        return x / 2;
    }
    return 3 * x + 1;
}

int Syracuse(long int x, int n)
{
    if(n == 0) return x;
    else return Syracuse(suivant(x), n - 1);
}

//Cette version récursive était très jolie mais plantait déjà pour la 4)f)
//Je l'ai donc refaite itérativement pour ne pas abuser de la mémoire utilisée
/*int temps_de_vol(int x)
{
    if(x == 1) return 1;
    else return 1 + temps_de_vol(suivant(x));
}*/

//Compte le nombre d'iterations necessaires pour que Syracuse(x) arrive a 1
int temps_de_vol(long int x)
{
    int tdv = 0;
    while(x != 1)
    {
        x = suivant(x);
        tdv++;
    }
    return tdv;
}

//Trouve le nombre x compris dans [1, N] ayant le plus long temps de vol
long int plus_long_vol(int N)
{
    long int x_max = 1;
    int tdv_max = 0;

    int tdv_local;
    //Pour chaque x, on voit si son temps de vol est plus long que l'ancien maximum
    for(long int x = 1; x <= N; x++)
    {
        tdv_local = temps_de_vol(x);
        if(tdv_local > tdv_max)
        {
            //Si c'est le cas, x devient le nouveau maximum de temps de vol 
            x_max = x;
            tdv_max = tdv_local;
        }
    }
    printf("Le temps de vol pour x = %ld est de %d.\n", x_max, tdv_max);
    return x_max;
}

void redige(int secondes)
{
    //Ecrit le nombre entier (positif) secondes sous la forme "Le temps mis est de m minutes et s secondes"
    int minutes = secondes / 60;
    secondes = secondes % 60;

    printf("Le temps pris est de ");
    if(minutes >= 1)
    {
        printf("%d minutes et ", minutes);
    }
    printf("%d secondes.\n", secondes);
}

int main()
{
    //Questions précédentes pour tester :
    /*
    printf("Pour x = 9, U6 = %d\n", Syracuse(9, 6));
    printf("Pour x = 77, U128 = %d\n", Syracuse(77, 128));
    printf("Pour x = 1023, U729 = %d\n", Syracuse(1023, 729));
    printf("Pour x = 1234567, U52397 = %d\n", Syracuse(1234567, 52397));
    
    printf("Le temps de vol de x = 1 est %d\n", temps_de_vol(1));
    printf("Le temps de vol de x = 26 est %d\n", temps_de_vol(26));
    printf("Le temps de vol de x = 27 est %d\n", temps_de_vol(27));
    printf("Le temps de vol de x = 28 est %d\n", temps_de_vol(28));
    printf("Le temps de vol de x = 77030 est %d\n", temps_de_vol(77030));
    printf("Le temps de vol de x = 77031 est %d\n", temps_de_vol(77031));
    */

    //Boucle "pour" hideuse, pour ne pas ecrire 12 lignes penibles
    for(long int N = 10; N <= 1000000; N *= 10)
    {
        printf("N = %ld : ", N);
        plus_long_vol(N);
    }
    
    //On calcule le temps mis pour la derniere question
    int temps_initial = time(NULL);
    printf("\nPour N = 10000000 : ");
    plus_long_vol(10000000);
    redige(time(NULL) - temps_initial);

    return 0;
}