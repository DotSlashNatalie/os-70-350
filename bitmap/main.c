#include <stdint.h>   /* for uint32_t */
#include <intrin.h>
#include <stdio.h>
	
int main()
{	
	unsigned int i = 0;
	unsigned int x;
	i |= 1 << 3; // or i |= 0x8; or i |= 8
	for(x = 0; x < 32; x++) // unsigned int = 32bits per ILP32
		if ((i & (1 << x)) == i)
			printf("%i\n", x);
	return 0;
}