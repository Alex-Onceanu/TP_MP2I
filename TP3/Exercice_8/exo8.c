#include <stdio.h>

//Un peu de récursivité, pour le spectacle

int Strlen(char* str)
{
    //Strlen et pas strlen sinon le compilateur se fache car il reconnait strings.h
    //On doit absolument mettre les 2 cas de base car ils couvrent des cas !=
    //Et sinon on fait un appel récursif sur ce qu'il reste du string en incrémentant
    if(str == NULL) return 0;
    if(*str == '\0') return 0;
    return 1 + Strlen(str + 1);
}

void epeler(char* str)
{
    //idem, on peut avoir *str == '\0' sans avoir str == NULL
    //Sinon on fait un appel récursif sur ce qu'il reste du string
    if(str == NULL) return;
    if(*str == '\0') return;
    printf("%c\n", *str);
    epeler(str + 1);
}

void Strcpy(char* dst, char* src)
{
    //On suppose que strlen(dst) >= strlen(src)
    //Possibilité d'utiliser memcpy depuis <stdlib.h>, mais ce n'est pas l'intérêt du TP
    if(dst == NULL || src == NULL) return;
    if(*src == '\0') return;
    *dst = *src;
    Strcpy(dst + 1, src + 1);
}

void Strcat(char* dst, char* src)
{
    //On suppose que dst contient déjà plein de cases allouées
    //Un vrai strcat() utiliserait malloc(sizeof(char) * (taille(dst) + taille(src)))
    if(dst == NULL || src == NULL) return;
    if(*src == '\0') return;

    //Au premier passage, on skip directement au '\0'
    int len = Strlen(dst);
    if(len > 0) 
    {
        Strcat(dst + len, src);
        return;
    }

    //Comme len == 0, on peut copier un par un chaque caractere de src
    //Dans dst, puis faire un appel récursif sur le reste de la chaîne
    *dst = *src;

    Strcat(dst + 1, src + 1);
}

int Strcmp(char* str1, char* str2)
{
    //On compare uniquement le premier caractère des deux string,
    //Il y a cinq cas possibles :
    //Soit il y a un probleme (on renvoie -2 si un parametre est nul)
    //Soit on est arrivés à la fin des deux strings en même temps, donc ils sont identiques
    //Sinon on traite les 3 cas donnés : soit on renvoie 1, soit -1
    //Et si on a aucun cas particulier sur le premier caractère des deux string,
    //alors on fait un appel récursif avec le caractère suivant.
    
    if(str1 == NULL || str2 == NULL) return -2;

    if(*str1 == '\0' && *str2 == '\0') return 0;
    if(*str1 > *str2) return 1;
    if(*str1 < *str2) return -1;

    return Strcmp(str1 + 1, str2 + 1);
}


int main()
{
    //Les tests sont là
    char test[60] = "Bonsoir m Rousseau !";
    char test2[] = "";
    char test3[] = "Hello to\0ut le monde !!!";

    printf("longueur : %d\n", Strlen(test));
    epeler(test);

    Strcat(test, test3);
    printf("\nApres un strcat : %s\n", test);

    Strcpy(test, test3);
    printf("Apres un strcpy : %s\n", test);
    
    printf("bonjour = bonjour : %d\naaaaa = aaaaaaaaaaaa : %d\n\'j\' = \"\" : %d\n", Strcmp("bonjour", "bonjour"), Strcmp("aaaa", "aaaaaaaaaaa"), Strcmp("j", test2));

    return 0;
}
