#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool fscan_ligne(FILE* f, char* str)
{
    //Lit une ligne du fichier f dans str.
    //S'arrete au premier \n, et le remplace par un \0.
    //Renvoie true si on arrive a la fin de f, false sinon
    int i = 0;
    char c;
    bool eof = false;
    while(c != '\n')
    {
        eof = (fscanf(f, "%c", &c) == EOF) || eof;
        str[i] = c;
        i++;
        if(eof) break;
    }
    str[i - 1] = '\0';
    return eof;
}

void trouve_mots(FILE* source, FILE* dest, char lettre)
{
    //Ecrit tous les mots de source commencant par 'lettre' dans dest.
    char ligne[30];
    while(!fscan_ligne(source, ligne))
    {
        //Mystere, enlever la ligne avec le printf fait planter le programme...
        //Je pense que le \n fait un flush de stdout que fflush ne fait pas
        //En tout cas si on enleve le printf on se retrouve avec un fichier
        //a.txt contenant le premier mot "angle" en boucle pendant 150Mo
        printf("\n");
        if(ligne[0] == lettre)
        {
            fprintf(dest, "%s\n", ligne);
        }
    }
    if(ligne[0] == lettre)
    {
        fprintf(dest, "%s\n", ligne);
    }
    //On remet le curseur au debut du fichier, pour les utilisations suivantes
    fseek(source, 0, SEEK_SET);
}

int main(int argc, char** argv)
{
    //Separe le fichier argv[1] en plein de petits fichiers avec uniquement
    //Les mots commencant par une certaine lettre, donnee en argv[2...argc-1]
    FILE* bouquin = fopen(argv[1], "r");

    //Pour chaque lettre, on cree un nouveau fichier .txt et on trouve les mots
    //Commencant par cette lettre grace a trouve_mots
    char nom_fichier[5] = "?.txt"; 
    for(int i = 2; i < argc; ++i)
    {
        nom_fichier[0] = argv[i][0];
        FILE* fichier_lettre = fopen(nom_fichier, "a");

        trouve_mots(bouquin, fichier_lettre, argv[i][0]);

        fclose(fichier_lettre);
    }

    fclose(bouquin);

    return 0;
}