#include <stdint.h>   /* for uint32_t */
#include <intrin.h> 
	
int main()
{	
	unsigned int i = 0;
	i |= 1 << 3; // or i |= 0x8; or i |= 8
	for(unsigned int x = 0; x < 32; x++) // unsigned int = 32bits per ILP32
		if ((i & (1 << x)) == i)
			cout << x << endl;
	return 0;
}