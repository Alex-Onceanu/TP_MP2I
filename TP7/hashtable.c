#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "hashtable.h"
#include "element.h"

//________________________________CHAINE______________________________________

CHAINE* chaine_vide()
{
    CHAINE* res = malloc(sizeof(CHAINE));
    
    res->taille = 0;
    res->tete = NULL;

    return res;
}

MAILLON* tete(CHAINE* c)
{
    assert(c != NULL);
    return c->tete;
}

int taille(CHAINE* c)
{
    assert(c != NULL);
    return c->taille;
}

MAILLON* suivant(MAILLON* m)
{
    assert(m != NULL);
    return m->suiv;
}

void maillon_free(MAILLON* m)
{
    //free(m->key);
    free(m);
}

void ajouter_debut(CHAINE* c, KEY k, VAL v)
{
    assert(c != NULL);

    MAILLON* nouv = malloc(sizeof(MAILLON));
    nouv->key = k;
    nouv->val = v;

    nouv->prec = NULL;
    nouv->suiv = c->tete;
    if(c->tete != NULL) c->tete->prec = nouv;

    c->tete = nouv;

    c->taille++;
}

MAILLON* recherche_chaine(CHAINE* c, KEY k)
{
    assert(c != NULL);
    MAILLON* curs = c->tete;
    for(int i = 0; i < c->taille; ++i)
    {
        if(strcmp(curs->key, k) == 0) return curs;
        curs = curs->suiv;
    }
    return NULL;
}

void supprimer_chaine(CHAINE* c, MAILLON* m)
{
    assert(c != NULL && m != NULL);
    if(m->prec == NULL)
    {
        c->tete = m->suiv;
    }
    else
    {
        m->prec->suiv = m->suiv;
    }
    if(m->suiv != NULL)
    {
        m->suiv->prec = m->prec;       
    }
    maillon_free(m);
    c->taille--;
}

void print_chaine(CHAINE* c)
{
    assert(c != NULL);
    MAILLON* curs = c->tete;
    printf("{\n");
    for(int i = 0; i < c->taille; ++i)
    {
        printf("( ");
        print_key(curs->key);
        printf(" : ");
        print_val(curs->val);
        printf(" ),\n");
        curs = curs->suiv;
    }
    printf("}\n");
}

void free_chaine(CHAINE* c)
{
    assert(c != NULL);
    if(taille(c) > 0)
    {
        MAILLON* curs = c->tete;
        for(int i = 0; i < c->taille - 1; ++i)
        {
            curs = curs->suiv;
            maillon_free(curs->prec);
        }
        maillon_free(curs);
    }
    free(c);
}

//___________________________________HASHMAP__________________________________

DICT* dict_vide(int taille)
{
    DICT* res = malloc(sizeof(DICT));
    res->m = taille;
    res->n = 0;

    res->t = malloc(res->m * sizeof(CHAINE*));
    for(int i = 0; i < res->m; ++i)
    {
        res->t[i] = chaine_vide();
    }

    return res;
}

VAL rechercher(DICT* d, KEY k)
{
    assert(d != NULL);

    int id = hash(k, d->m);
    MAILLON* trouvaille = recherche_chaine(d->t[id], k);

    if(trouvaille == NULL) return -1;
    return trouvaille->val;
}

bool appartient(DICT* d, KEY k)
{
    assert(d != NULL);

    return rechercher(d, k) != -1;
}

void inserer(DICT* d, KEY k, VAL v)
{
    assert(d != NULL);
    assert(v >= 0);

    int id = hash(k, d->m);
    ajouter_debut(d->t[id], k, v);
    d->n++;
}

void supprimer(DICT* d, KEY k)
{
    assert(d != NULL);

    int id = hash(k, d->m);
    MAILLON* trouvaille = recherche_chaine(d->t[id], k);

    supprimer_chaine(d->t[id], trouvaille);
}

void print_dict(DICT* d)
{
    assert(d != NULL);

    MAILLON* curs = NULL;
    for(int i = 0; i < d->m; ++i)
    {
        curs = d->t[i]->tete;
        while(curs != NULL)
        {
            printf("%s -> %d\n", curs->key, curs->val);
            curs = curs->suiv;
        }
    }
}

void debug_dict(DICT* d)
{
    assert(d != NULL);

    MAILLON* curs = NULL;
    for(int i = 0; i < d->m; ++i)
    {
        curs = d->t[i]->tete;
        printf("Alveole %d (taille %d):\n", i, taille(d->t[i]));
        while(curs != NULL)
        {
            printf("%s -> %d\n", curs->key, curs->val);
            curs = curs->suiv;
        }
        printf("\n");
    }
}

void free_dict(DICT* d)
{
    assert(d != NULL);

    for(int i = 0; i < d->m; ++i)
    {
        free_chaine(d->t[i]);
    }
    free(d->t);
    free(d);
}

//____________________Fonctionalites additionnelles___________________________

void free_keys(DICT* d)
{
    assert(d != NULL);

    MAILLON* curs = NULL;
    for(int i = 0; i < d->m; ++i)
    {
        curs = d->t[i]->tete;
        while(curs != NULL)
        {
            free(curs->key);
            curs = curs->suiv;
        }
    }
}

char* trouver_max(DICT* d)
{
    assert(d != NULL);

    MAILLON* curs = NULL;
    VAL val_max = -1;

    const int MAXBUF = 30; //anticonstitutionnellement : 25 lettres
    char* id_associe = malloc((MAXBUF + 1) * sizeof(char));
    for(int j = 0; j < MAXBUF; ++j) id_associe[j] = ' ';
    
    int id_length = 0;

    for(int i = 0; i < d->m; ++i)
    {
        curs = d->t[i]->tete;
        while(curs != NULL)
        {
            if(curs->val > val_max)
            {
                val_max = curs->val;
                strcpy(id_associe, curs->key);
                id_length = strlen(curs->key);
            }
            curs = curs->suiv;
        }
    }
    id_associe[id_length] = '\0';
    return id_associe;
}

float taille_moyenne_alveoles(DICT* d)
{
    assert(d != NULL);

    float somme = 0;
    float compt = 0;

    for(int i = 0; i < d->m; ++i)
    {
        if(taille(d->t[i]) != 0) compt++;
        somme += taille(d->t[i]);
    }

    return somme / compt;
}

//Renvoie un dictionnaire contenant les mots de taille >= K avec leur nb d'occ
DICT* construit_dictionnaire_occurences(char* filename, int K, int m, int* nb_mots)
{
    FILE* f = fopen(filename, "r");

    DICT* d = dict_vide(m);
    char* str = malloc(100 * sizeof(char));
    int l = 0;
    while(fscanf(f, "%s", str) != EOF)
    {
        (*nb_mots)++;
        l = strlen(str);
        if(l < K) continue;
        
        if(appartient(d, str))
        {
            int id = hash(str, d->m);
            MAILLON* trouvaille = recherche_chaine(d->t[id], str);
            trouvaille->val++;
        }
        else
        {
            char* mot = malloc((l + 1) * sizeof(char));
            strcpy(mot, str);
            inserer(d, mot, 1);
        }
    }
    
    free(str);
    fclose(f);

    return d;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

//Fonction tres maladroite mais il est 21h50 je dois rendre le TP
//Elle fonctionne cependant, c'est juste qu'il reste de la réfactorisation à faire
//Et meme, l'algo n'est pas opti..
void mots_plus_frequents(char* filename, int K, int n_mots)
{
    int nb_mots = 0;
    DICT* d = construit_dictionnaire_occurences(filename, K, 8191, &nb_mots);

    char** every_max = malloc(sizeof(char*) * n_mots);
    int* every_val = malloc(sizeof(int) * n_mots);
    int compt_every = 0;

    int valmax = 0;
    char* plus_frequent = trouver_max(d);
    assert(appartient(d, plus_frequent));

    while(compt_every < min(n_mots, d->n))
    {
        //Horreur indescriptible : 

        every_max[compt_every] = trouver_max(d);
        every_val[compt_every] = rechercher(d, every_max[compt_every]);

        if(every_val[compt_every] == -2) break;

        int id = hash(every_max[compt_every], d->m);
        MAILLON* trouvaille = recherche_chaine(d->t[id], every_max[compt_every]);
        trouvaille->val = -2;

        printf("%s\n", every_max[compt_every]);
        compt_every++;
    }

    for(int i = 0; i < compt_every; ++i)
    {
        int id = hash(every_max[i], d->m);
        MAILLON* trouvaille = recherche_chaine(d->t[id], every_max[i]);
        trouvaille->val = every_val[i];
    }

    free(every_val);
    free(every_max);
    free_keys(d);
    free_dict(d);
}

void mot_plus_frequent(char* filename, int K, int m)
{
    int nb_mots = 0;
    DICT* d = construit_dictionnaire_occurences(filename, K, m, &nb_mots);

    char* plus_frequent = trouver_max(d);
    assert(appartient(d, plus_frequent));

    printf("Le fichier \"%s\" contient %d mots.\nLe mot le plus frequent de taille >= %d est \"%s\", \
avec %d occurences.\n", filename, nb_mots, K, plus_frequent, rechercher(d, plus_frequent));

    float moyenne = taille_moyenne_alveoles(d);

    printf("La taille moyenne des alveoles non-vides est de %f.\n", moyenne);

    free(plus_frequent);
    free_keys(d);
    free_dict(d);
}