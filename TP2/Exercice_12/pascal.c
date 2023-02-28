#include <stdio.h>
#include <assert.h>

/*
Le triangle de Pascal est une facon d'afficher tous les coefficients binomiaux
(sous la forme d'un triangle) tels que :
la somme de deux coefficients adjacents donnent le coefficient d'en dessous.
Il y a enormement de proprietes avec ce triangle (la somme des colonnes, celle
des diagonales, donnent des resultats assez impressionnants.)
Il reste utile pour trouver rapidement les coefficients presents lors du
developpement de (a + b)**n

En tout cas, ce programme demande a l'utilisateur un certain nombre de lignes 
de ce triangle a afficher, et les affiche dans le terminal.
*/

//Comme un scanf, mais en mieux.
int meilleur_scanf(char* texte_a_afficher, int nb_min, int nb_max)
{
    //Affiche un prompt dans le terminal pour demander a l'utilisateur un nombre
    //Puis s'assure que ce nombre est correct avant de le renvoyer.
    int entree;
    printf("%s", texte_a_afficher);
    scanf("%d", &entree);
    while(getchar() != '\n');

    if(entree < nb_min || entree > nb_max)
    {
        //On demande a l'utiliser de re-entrer un nombre jusqu'a ce qu'il soit correct.
        printf("Le nombre N doit etre un entier compris entre %d et %d. Veuillez reessayer.\n"
            , nb_min, nb_max);
        return meilleur_scanf(texte_a_afficher, nb_min, nb_max);
    }
    return entree;
}

//Renvoie le coefficient binomial k parmi n, k compris entre 0 et n.
//Cet algorithme utilise la formule de pascal recursivement, ce qui n'est pas du tout optimal..
//Neanmoins, pour un n inferieur a 25 elle reste satisfaisante.
//On pourrait l'optimiser en utilisant la memoisation (comme a l'exo sur Syracuse)
//Mais la fonction perdrait alors en elegance. Voici donc une fonction elegante mais lente : 
int pascal(int k, int n)
{
    assert(k <= n);
    assert(k >= 0);

    //Un cas de base : la convention dit que 0 parmi n pour tout n vaut 1, idem pour k = n
    if(k == n || k == 0) return 1; 
    //On utilise la formule de pascal : binom(k, n) + binom(k + 1, n) = binom(k + 1, n + 1)
    return pascal(k-1, n-1) + pascal(k, n-1);
}

//Demande a l'utilisateur un nombre de lignes a afficher,
//Puis affiche dans le terminal autant de lignes du triangle de pascal.
int main()
{
    //Prend en entree un nombre N_MAX (compris entre 0 et 25) de lignes a afficher.
    int N_MAX = meilleur_scanf("Combien de lignes pour le triangle de Pascal ? : ", 0, 25);

    //Boucles imbriquees : tant qu'il reste des lignes a afficher,
    int n = 0;
    while(n < N_MAX)
    {
        //Et pour chaque colonne de la ligne, affiche le coefficient en question
        for(int k = 0; k <= n; k++)
        {
            printf("%d ", pascal(k, n));
        }
        //Saute une ligne a la fin de la ligne du triangle, et on passe a la ligne suivante.
        printf("\n");
        n++;
    }
    return 0;
}

/*
Toute valeur negative ou superieure a 25 ne sera pas prise en compte
(et toute entree qui n'est pas un nombre entier).
Donc oui, les tests pour des valeurs etranges fonctionnent.

La valeur maximale est de 25 car au bout d'un moment les valeurs ne rentrent plus sur une seule ligne
(et donc le resultat devient incomprehensible)
Deja pour n = 25 le triangle est immense...

Triangle complet pour n = 25 :
1
1 1
1 2 1
1 3 3 1
1 4 6 4 1
1 5 10 10 5 1
1 6 15 20 15 6 1
1 7 21 35 35 21 7 1
1 8 28 56 70 56 28 8 1
1 9 36 84 126 126 84 36 9 1
1 10 45 120 210 252 210 120 45 10 1
1 11 55 165 330 462 462 330 165 55 11 1
1 12 66 220 495 792 924 792 495 220 66 12 1
1 13 78 286 715 1287 1716 1716 1287 715 286 78 13 1
1 14 91 364 1001 2002 3003 3432 3003 2002 1001 364 91 14 1
1 15 105 455 1365 3003 5005 6435 6435 5005 3003 1365 455 105 15 1
1 16 120 560 1820 4368 8008 11440 12870 11440 8008 4368 1820 560 120 16 1
1 17 136 680 2380 6188 12376 19448 24310 24310 19448 12376 6188 2380 680 136 17 1
1 18 153 816 3060 8568 18564 31824 43758 48620 43758 31824 18564 8568 3060 816 153 18 1
1 19 171 969 3876 11628 27132 50388 75582 92378 92378 75582 50388 27132 11628 3876 969 171 19 1
1 20 190 1140 4845 15504 38760 77520 125970 167960 184756 167960 125970 77520 38760 15504 4845 1140 190 20 1
1 21 210 1330 5985 20349 54264 116280 203490 293930 352716 352716 293930 203490 116280 54264 20349 5985 1330 210 21 1
1 22 231 1540 7315 26334 74613 170544 319770 497420 646646 705432 646646 497420 319770 170544 74613 26334 7315 1540 231 22 1
1 23 253 1771 8855 33649 100947 245157 490314 817190 1144066 1352078 1352078 1144066 817190 490314 245157 100947 33649 8855 1771 253 23 1
1 24 276 2024 10626 42504 134596 346104 735471 1307504 1961256 2496144 2704156 2496144 1961256 1307504 735471 346104 134596 42504 10626 2024 276 24 1
*/