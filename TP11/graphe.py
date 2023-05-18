import matplotlib.pyplot as plt
from math import sqrt
import numpy as np

n_min = 20
n_max = 20021
pas = 1000


#On observe une évolution en O(n²) pour les A n
#(après avoir remarqué que la courbe sqrt(t)(n) est linéaire)
#Cela s'explique par le fait que notre arbre se comporte comme une liste chaînée
#(puisque c'est un peigne, vu qu'on insere par ordre croissant sans équilibrer)
#Donc a chaque insertion le cout est en O(taille_actuelle), et il y a n insertions...
#Donc O(n²)
n = [n_min + i * pas for i in range(int(1 + n_max / pas))]
abr = [5.99999999906231096e-06, 0.0142919999999975289, 0.0583409999999986439, 0.134510999999996272, 0.245289999999990016, 0.386742000000012354, 0.562499999999992895, 0.792384000000005528, 1.05443199999999848, 1.35721600000000109, 1.7389349999999979, 2.13429299999999955, 2.60480399999999435, 3.06976299999999469, 3.60661000000000342, 4.21522199999999714, 4.88388099999999881, 5.63670300000000069, 6.47733, 7.276762, 8.32177699999999909]

#Pour les B n, on devrait observer une évolution en O(n * log2(n))
#Puisque chaque insertion est en O(hauteur), et il y a n insertions
#Et on a démontré que la hauteur est de l'ordre de 2 * log2(2 * n + 1)
#Cependant ! Ce n'est pas le cas :(
#L'ARN a bien une hauteur bornée, et les B n sont assez bien équilibrés
#Mais le problème vient de la fonction d'insertionARN : bien qu'elle fasse
#bien moins d'appels récursifs que celle pour les ABR, comme chaque appel est
#plus lent (à cause de la correction, peut-être ?), au final l'ARN est
#en pratique plus lent que le peigne.
#Je n'ai pas trouvé la cause exacte de ce résultat, je me suis peut-être trompé
#dans une de mes fonctions mais j'arrive pas à trouver pourquoi c'est plus lent 
#alors qu'il y a bien moins d'appels récursifs faits
#Peut-être qu'en récursif terminal le programme serait plus rapide ? Pourtant,
#pour les ABR les fonctions de création des A n ne sont pas récursives terminales non plus...

arn = [7.00000000009026735e-06, 0.000729999999999897398, 0.00173899999999993504, 0.00273699999999998944, 0.00370399999999992957, 0.00471100000000013175, 0.00564100000000000712, 0.00679099999999999149, 0.00811399999999995458, 0.00922100000000014575, 0.0105990000000000251, 0.0115520000000000067, 0.0123030000000001749, 0.0136469999999999647, 0.0153399999999999093, 0.0159209999999998519, 0.017531999999999881, 0.0196770000000001666, 0.0222350000000000048, 0.0265849999999998587, 0.0373820000000000263]

#plt.yscale('log')
plt.plot(n, abr) 
plt.plot(n, arn)
plt.show()