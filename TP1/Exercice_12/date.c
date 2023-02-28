//Affiche l'année et le mois actuel.

#include <stdio.h>
#include <time.h>

int main()
{
    long int secondes = time(NULL);

    //On convertit le nb de secondes depuis 1970 en jours
    long int jours = secondes / (60*60*24);
    //A partir du nb de jours on peut déduire l'an et le mois
    long int an = (jours / 365) + 1970.0; 
    long int mois = (jours % 365) / 30;

    //On doit s'assurer que le mois est un nombre valide, pour pas dépasser le calendrier..
    if(mois < 0 || mois > 11) return -1;
    //Tableau de chaque nom de mois à son bon index, calendrier[mois] est le nom du mois actuel.
    char* calendrier[] = { "janvier", "fevrier", "mars", "avril", "mai", "juin", "juillet", "aout", "septembre", "octobre", "novembre", "decembre"};
    printf("Nous sommes en %s de l'an %ld\n", calendrier[mois], an);

    return 0;
}