#include <stdio.h>

//L'utilisateur rentre plein de nombre positifs, au premier nombre
//négatif le programme s'arrête et affiche la somme des nombres
int main()
{
    int somme = 0;
    int n = 0;

    //Une boucle do/while pour ne pas devoir mettre de >= au lieu du >
    do {
        somme += n;
        printf("Rentrez un nombre a sommer ! : ");
        scanf("%d", &n);
    }while(n > 0);

    printf("Le nombre final vaut %d\n", somme);

    return 0;
}