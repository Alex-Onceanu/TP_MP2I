#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct eleve{
    char nom_complet[40];
    int jour;
    int mois;
    int annee;
    char metier[40];
}eleve_t;


void eleve_presentation(eleve_t e)
{
    //Affiche dans stdout les attributs d'un eleve e.
    //%s ne fonctionne pas s'il n'est pas suivi d'un \n pour flush apparemment?
    //et fflush(stdout) n'arrange rien, c'est bizarre..
    printf("Eleve %s\n\tne le %d/%d/%d, devenu %s\n\n",
            e.nom_complet, e.jour, e.mois, e.annee, e.metier);
}

void scan_ligne(char* str)
{
    //Lit une ligne de stdin dans str.
    //S'arrete au premier \n, et le remplace par un \0.
    int i = 0;
    char c;
    while(c != '\n')
    {
        scanf("%c", &c);
        str[i++] = c;
    }
    str[i - 1] = '\0';
}

void fscan_ligne(FILE* f, char* str)
{
    //Lit une ligne du fichier f dans str.
    //S'arrete au premier \n, et le remplace par un \0.
    int i = 0;
    char c;
    while(c != '\n')
    {
        fscanf(f, "%c", &c);
        str[i] = c;
        i++;
    }
    str[i - 1] = '\0';
}

int main()
{
    //On demande a l'utilisateur un nom de fichier
    char nom_fichier[20];
    printf("Nom de fichier ? (maximum 20 caracteres) : ");
    scan_ligne(nom_fichier);

    FILE* fichier = fopen(nom_fichier, "r");
    if(fichier == NULL)
    {
        fprintf(stderr, "Le fichier %s est introuvable.", nom_fichier);
        return -1;    
    }

    //On lit la premiere ligne, qui est le nombre total d'eleves dans la promo.
    int nb_eleves = 0;
    fscanf(fichier, "%d", &nb_eleves);
    
    printf("La promo comporte %d eleves.\n\n", nb_eleves);
    //Pour se debarrasser du \n
    fseek(fichier, 2, SEEK_CUR);

    //Puis chaque ligne correspond a un eleve, on lit ses informations pour les afficher.
    eleve_t tmp;
    for(int i = 0; i < nb_eleves; i++)
    {
        fscan_ligne(fichier, tmp.nom_complet);

        fscanf(fichier, "%d", &(tmp.jour));
        fscanf(fichier, "%d", &(tmp.mois));
        fscanf(fichier, "%d", &(tmp.annee));

        //Pour se debarrasser du \n
        fseek(fichier, 1, SEEK_CUR);
        fscan_ligne(fichier, tmp.metier);

        eleve_presentation(tmp);
    }

    fclose(fichier);

    return 0;
}


//Je finirai donc ethnologue informatique...