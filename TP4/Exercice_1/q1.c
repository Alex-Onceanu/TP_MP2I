#include <stdio.h>
#include <stdlib.h>

//Renvoie un tableau de n entiers égaux à 0
int* creer_tableau(unsigned int n)
{
    int* t = malloc(n * sizeof(int));
    for(int i = 0; i < n; ++i)
    {
        t[i] = 0;
    }
    return t;
}

//Renvoie un tableau 2D de n * m entiers égaux à 0
int** creer_tableau_2d(unsigned int n, unsigned int m)
{
    int** t = malloc(n * sizeof(int *));
    for(int i = 0; i < n; ++i)
    {
        t[i] = malloc(m * sizeof(int));
        for(int j = 0; j < m; ++j)
        {
            t[i][j] = 0;
        }
    }
    return t;
}

//lance free sur chaque ligne du tableau t contenant nb_lignes lignes
void libere_tableau_2d(int** t, unsigned int nb_lignes)
{
    for(int j = 0; j < nb_lignes; ++j)
    {
        free(t[j]);
    }
    free(t);
}

int main()
{
    const int N = 5;
    const int M = 7;
    int** tab = creer_tableau_2d(N, M);
    
    //On affiche tout le contenu du tableau 2D
    for(int y = 0; y < N; ++y)
    {
        for(int x = 0; x < M; ++x)
        {
            printf("tab[%d][%d] = %d\n", y, x, tab[y][x]);
        }
    }

    //On libère tout le tableau 2D
    libere_tableau_2d(tab, N);
    return 0;
}