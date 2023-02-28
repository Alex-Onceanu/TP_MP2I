#include <stdio.h>
#include <stdbool.h>

int main()
{
    bool a = true;
    bool b = false;

    printf("a : %d\nb : %d\na && b : %d\na || b : %d\n!a : %d\n"
        , a, b, a && b, a || b, !a);

    return 0;
}