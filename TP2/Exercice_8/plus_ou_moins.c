//j'ai déjà fait ce programme à la question libre du TP1...

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
    Le jeu du "plus ou moins" fait deviner à l'utilisateur un nombre mystère,
    compris entre 1 et 100 et déterminé aléatoirement au lancement du programme.
    A chaque essai, le programme dit à l'utilisateur si le nombre cherché est 
    plus petit ou plus grand que ce qu'a rentré l'utilisateur.
    A la fin, le programme donnera à l'utilisateur le temps qu'il a mis pour trouver le nombre.
    (en secondes ou bien minutes:secondes selon la durée)
*/

int randint(unsigned int maximum)
{
    //Renvoie un nombre entier compris dans [0,maximum]
    if(maximum < 0) return 0;
    return rand() % maximum;
}

int obtenir_tentative()
{
    //Demande à l'utilisateur de rentrer un nombre, puis renvoie le nombre donné en saisie.
    
    //-2 car -1 est déjà le code pour arrêter le programme.
    int tentative = -2;
    printf("Essayez de deviner le nombre mystere (compris entre 0 et 4999): ");
    scanf("%d", &tentative);

    //Ligne nécessaire pour pas que le programme tourne indéfiniment au cas où l'utilisateur écrit n'importe quoi.
    //( = tant qu'il reste des caractères dans le flux d'entrée, s'en débarrasser.)
    while(getchar() != '\n');

    if(tentative == -1) exit(0);
    
    if(!tentative || tentative < 0 || tentative > 4999)
    {
        //Si l'utilisateur écrit n'importe quoi, on lui demande de réessayer jusqu'à ce qu'il envoie quelque chose de correct.
        printf("Merci de rentrer un nombre entier compris entre 0 et 4999.\n");
        
        return obtenir_tentative();
    }

    return tentative;
}

void compare(int n, int mystere)
{
    //Compare n et mystere, donne une indication à l'utilisateur en fonction de s'il est trop grand ou trop petit.
    if(n == mystere) return;
    if(n < mystere)
    {
        printf("Plus haut !\n");
    }
    else
    {
        printf("Plus bas !\n");
    }
}

int main()
{
    //On initialise le générateur de nombres, et le nombre mystère à chercher.
    srand(time(NULL));

    int nb_mystere = randint(5000);
    int tentative = -1;

    printf("Vous pouvez quitter le jeu a tout moment en ecrivant '-1'.\n");

    //Boucle principale du jeu
    while(tentative != nb_mystere)
    {
        //Tant que le joueur n'a pas trouvé, on lui fait deviner le nombre et on lui donne un indice.
        tentative = obtenir_tentative();
        compare(tentative, nb_mystere);
    }

    printf("Gagne !\n");

    return 0;
}