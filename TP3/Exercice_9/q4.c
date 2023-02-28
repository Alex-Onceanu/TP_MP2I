#include <stdio.h>
#include <stdbool.h>

#define MAX_PRIME 10000
#define N 6


bool is_prime[MAX_PRIME];

void initialise_is_prime()
{
    /* initalisation de is_prime. Au départ, on considère que tous les nombres 
	 * sont premiers, et on va les filtrer / les passer au crible
	 */
	for (int i = 0; i < MAX_PRIME; ++i)
	{
		is_prime[i] = true;
	}
	is_prime[0] = false;
	is_prime[1] = false;

	for (int i = 0; i < MAX_PRIME; ++i)
	{
		// si i est premier, on retire tous ses multiples entre 2i et n-1 
		if (is_prime[i]){
			for (int k = 2; k <= MAX_PRIME/i; ++k)
			{
				is_prime[k*i] = false;
			}
		}
	}
}


void affiche_char(int matrix[N][N])
{
    if(matrix == NULL) return;

    for(int y = 0; y < N; ++y)
    {
        for(int x = 0; x < N; ++x)
        {
            //Pour l'affichage joli, on peut écrire %2d pour que tout
            //nombre soit affiché avec 2 chiffres, donc tout s'aligne
            printf("%2c ", matrix[y][x]);
        }
        printf("\n");
    }
}

bool premier(int n)
{
    return is_prime[n];
}

int anneau_ulam(int tab[N][N], int y0, int x0, int val_init, int taille)
{
    if(tab == NULL) return 0;

    int i = val_init;
    int x = x0;
    int y = y0;

    for(; x < taille + x0; ++x)
    {
        tab[y][x] = premier(i--) ? 'X' : ' ';
    }
    for(; y < taille + y0; ++y)
    {
        tab[y][x] = premier(i--) ? 'X' : ' ';
    }
    for(; x > x0; --x)
    {
        tab[y][x] = premier(i--) ? 'X' : ' ';
    }
    for(; y > y0; --y)
    {
        tab[y][x] = premier(i--) ? 'X' : ' ';
    }
    return i;
}

void Ulam(int matrix[N][N])
{
    int val_init = N * N;
    for(int n = 0; n < N/2; ++n)
    {
        val_init = anneau_ulam(matrix, n , n, val_init, N - (2*n + 1));
    }
    if(N % 2 == 1)
    {
        matrix[N/2][N/2] = premier(val_init) ? 'X' : ' ';
    }
}

int main()
{
    initialise_is_prime();
    int matrice_ulam[N][N];
    Ulam(matrice_ulam);
    affiche_char(matrice_ulam);

    return 0;
}