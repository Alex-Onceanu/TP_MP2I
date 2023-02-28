#include <stdio.h>

#define N 10
#define M 10

void remplit_somme(int matrix[N][M], int n, int m)
{
    //L'élément de coordonnées (x, y) aura pour valeur x + y
    if(matrix == NULL) return;

    for(int y = 0; y < n; ++y)
    {
        for(int x = 0; x < m; ++x)
        {
            matrix[y][x] = y + x;
        }
    }
}

void affiche_matrice(int matrix[N][M], int n, int m)
{
    if(matrix == NULL) return;

    for(int y = 0; y < n; ++y)
    {
        for(int x = 0; x < m; ++x)
        {
            //Pour l'affichage joli, on peut écrire %2d pour que tout
            //nombre soit affiché avec 2 chiffres, donc tout s'aligne
            printf("%2d ", matrix[y][x]);
        }
        printf("\n");
    }
}

int main()
{
    int enter_the_matrix[N][M];
    remplit_somme(enter_the_matrix, N, M);
    affiche_matrice(enter_the_matrix, N, M);
    
    return 0;
}