#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

//Renvoie si oui ou non a est divisible par b (b non nul)
bool divisible(int a, int b)
{
    assert(b != 0);
    return a % b == 0;
}

//Affiche x et 1/x, x étant un nombre flottant non nul
void inverse(float x)
{
    assert(x != 0);
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
    printf("9 | 72 :%d\n9 | 3 : %d\n",
        divisible(72, 9), divisible(3, 9));

    inverse(3);
    inverse(2.0/3.0);
    inverse(0);

    //assertion non vérifiée, on demande l'inverse de 0.

    return 0;
}