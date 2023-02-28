#include <stdio.h>

#define N 9

void affiche_matrice(int matrix[N][N])
{
    if(matrix == NULL) return;

    for(int y = 0; y < N; ++y)
    {
        for(int x = 0; x < N; ++x)
        {
            //Pour l'affichage joli, on peut écrire %2d pour que tout
            //nombre soit affiché avec 2 chiffres, donc tout s'aligne
            printf("%2d ", matrix[y][x]);
        }
        printf("\n");
    }
}

#if 0
//Pour les tests, une fonction qui remplit une matrice avec des 0

void clear_matrix(int matrix[N][N])
{
    if(matrix == NULL) return;

    for(int y = 0; y < N; ++y)
    {
        for(int x = 0; x < N; ++x)
        {
            matrix[y][x] = 0;
        }
    }
}
#endif

int anneau(int tab[N][N], int y0, int x0, int val_init, int taille)
{
    if(tab == NULL) return 0;

    //On décompose de façon linéaire et naïve le processus
    //en 4 étapes, comme on remplirait l'anneau à la main.
    int i = val_init;
    int x = x0;
    int y = y0;

    for(; x < taille + x0; ++x)
    {
        tab[y][x] = i++;
    }
    for(; y < taille + y0; ++y)
    {
        tab[y][x] = i++;
    }
    for(; x > x0; --x)
    {
        tab[y][x] = i++;
    }
    for(; y > y0; --y)
    {
        tab[y][x] = i++;
    }
    return i;
}

void spirale(int matrix[N][N])
{
    //On remplit chaque anneau successivement, ça donne une spirale.
    //Une matrice N*N aura N/2 anneaux
    int val_init = 0;
    for(int n = 0; n < N/2; ++n)
    {
        val_init = anneau(matrix, n , n, val_init, N - (2*n + 1));
    }
    //En cas de N impair il reste la case centrale à remplir
    if(N % 2 == 1)
    {
        matrix[N/2][N/2] = val_init;
    }
}

int anneau_inverse(int tab[N][N], int y0, int x0, int val_init, int taille)
{
    //Idem que pour anneau mais avec des i-- au lieu de i++
    if(tab == NULL) return 0;

    int i = val_init;
    int x = x0;
    int y = y0;

    for(; x < taille + x0; ++x)
    {
        tab[y][x] = i--;
    }
    for(; y < taille + y0; ++y)
    {
        tab[y][x] = i--;
    }
    for(; x > x0; --x)
    {
        tab[y][x] = i--;
    }
    for(; y > y0; --y)
    {
        tab[y][x] = i--;
    }
    return i;
}

int spirale_inverse(int matrix[N][N])
{
    //idem que spirale mais en utilisant anneau_inverse
    int val_init = N * N;
    for(int n = 0; n < N/2; ++n)
    {
        val_init = anneau_inverse(matrix, n , n, val_init, N - (2*n + 1));
    }
    if(N % 2 == 1)
    {
        matrix[N/2][N/2] = val_init;
    }
}


int main()
{
    //Un test basique
    int enter_the_matrix[N][N];
    spirale_inverse(enter_the_matrix);
    affiche_matrice(enter_the_matrix);

    return 0;
}