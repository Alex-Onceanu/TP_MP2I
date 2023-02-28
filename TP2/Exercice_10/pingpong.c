#include <stdio.h>
#include <unistd.h>

//On définit la constante 1 seconde = 10**6 µs
#define SECONDE 1000000

//On déclare pong pour pouvoir l'utiliser depuis ping avant de l'avoir définie.
void pong();

void ping()
{
    printf("Ping\n");
    usleep(SECONDE);
    pong();
}

void pong()
{
    printf("Pong\n");
    usleep(SECONDE);
    ping();
}

int main()
{
    ping();
    return 0;
}