#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randint(unsigned int minimum, unsigned int maximum)
{
    //Renvoie un entier aléatoire entre minimum et maximum (compris)
    if(minimum > maximum) 
    {
        //On inverse minimum et maximum si min > max
        int tmp = minimum;
        minimum = maximum;
        maximum = tmp;
    }

    return (rand() % (maximum + 1 - minimum)) + minimum;
}

int main()
{
    srand(time(NULL));

    int a = randint(10,20);
    int b = randint(10,20);
    int c = randint(10,20);

    printf("Trois nombres aléatoires : %d, %d, %d\n\n", a,b,c);

    return 0;
}