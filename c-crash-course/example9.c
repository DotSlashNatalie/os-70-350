// C - also works in C++
#include <stdio.h>
#include <stdlib.h>

void f(int * x)
{
	*x = 4; // This is dangerous as x could be NULL but for the sake of a simple example - we will assume it won't ever be
}

int main()
{
	int * i = malloc(sizeof(int));
	f(i);
	printf("%i", i);
	free(i);
}