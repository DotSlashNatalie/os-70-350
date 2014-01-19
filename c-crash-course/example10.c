//C - could also do this - valid in C++ as well
#include <stdio.h>
#include <stdlib.h>

void f(int * i)
{
        *i = 4;
}

int main()
{
        int x = 10;
        f(&x);
        printf("%i", x);
        return 0;
}