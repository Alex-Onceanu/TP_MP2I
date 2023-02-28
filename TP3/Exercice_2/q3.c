#include <stdio.h>
#include <assert.h>

void echange(int* x, int* y){
    //Inverse les valeurs des variables pointées par les pointeurs x et y
	assert(x != NULL && y != NULL);
    int t = *x;
    *x = *y;
    *y = t;
}

void g(int **x, int *y){ // int *y veut dire pareil que int* y
	assert(x != NULL && y != NULL);
    *x = y;
    *y += 1;
}

int main()
{
    int a = 5, b = 8;
    int* p = &a;
    printf("Etape 1: %d %d %d\n\n", a, b, *p);
    
    f(&a, &b);
    printf("Etape 2: %d %d %d\n\n", a, b, *p);

    g(&p, &b);
    printf("Etape 3: %d %d %d\n\n", a, b, *p);
    
    return 0;
}