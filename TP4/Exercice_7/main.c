#include <stdio.h>
#include <stdlib.h>

#include "choix.h"
#include "page.h"
#include "livre.h"

/*
Attention, le programme ne marchera qu'avec des fichiers dont les sauts de
ligne s'écrivent avec un simple \n, et pas \r\n comme sur windows.
Donc ce programme ne fonctionnera pas avec le fichier aventure.txt de
l'archive, (car il faudrait remplacer les fseek(,1,) par des fseek(,2,))
Mais j'ai inventé une petite histoire dans le fichier livre.txt, avec le
bon format. Bonne chance pour obtenir la fin "VICTOIRE !!!" :) .
*/

//Indiquer le nom du fichier a lire en parametre du programme.
int main(int argc, char** argv)
{
    if(argc != 2) return -1;
    
    //On lit le fichier texte et le convertir en structure livre.
    livre_p aventure = generer_livre(argv[1]);
    if(aventure == NULL) return -1;

    //On lance le jeu avec le livre.
    LDVELH(aventure);

    //Puis on libere toute la memoire a la fin de la partie.
    free_livre(aventure);

    return 0;
}