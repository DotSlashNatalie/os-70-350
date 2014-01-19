// C example

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int * i = malloc(sizeof(int));
	*i = 5;
	printf("%i", *i);
	return 0;
}