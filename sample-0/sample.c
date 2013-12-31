#include <stdio.h>

int main()
{
        int x[10];
        int i;
        int * z = NULL;
        for(i = 0; i < 10; i++)
                printf("%i", i+*z);
        return 0;
}
