// Pointers are variables that point to blocks of memory
// C++
#include <iostream>

int main()
{
	int * i = new int(5);
	// In order to view that block of memory you must look at 
	std::cout << *i << std::endl;
	delete i;
}