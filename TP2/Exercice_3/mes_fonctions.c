#include <stdio.h>
#include <stdbool.h>

//Renvoie si oui ou non a est divisible par b
bool divisible(int a, int b)
{
    if(b == 0) return false;
    return a % b == 0;
}

//Affiche x et 1/x, x étant un nombre flottant
void inverse(float x)
{
    if(x == 0) return;
    printf("x = %f\n1/x = %f\n", x, 1/x);
}

//Calcule 3x + 5y - 6.25z + t, l'affiche et renvoie son carré
float calcul_litteral(float x, float y, float z, float t)
{
    float gros_calcul = 3*x + 5*y - 6.25*z + t;
    printf("3*%f + 5*%f - 6.25*%f + %f = %f", x, y, z, t, gros_calcul);
    
    return gros_calcul * gros_calcul;
}

//On teste les fonctions précédentes pour différentes valeurs
int main()
{
    printf("9 | 72 :%d\n9 | 3 : %d\n0 | 1 : %d\n\n",
        divisible(72, 9), divisible(3, 9), divisible(1, 0));

    inverse(3);
    inverse(2.0/3.0);
    inverse(0);

    printf("\n");
    float c_1 = calcul_litteral(2,8,6,9);
    printf(" et au carre donne %f\n", c_1);

    float c_2 = calcul_litteral(3.8, 7.9, -40, 0);
    printf(" et au carre donne %f\n", c_2);

    float c_3 = calcul_litteral(0,0,0,0);
    printf(" et au carre donne %f\n", c_3);

    return 0;
}