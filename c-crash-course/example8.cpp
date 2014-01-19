// However, C and C++ does support passing by reference

// C++
#include <iostream>

void f(int & x)
{
	x = 4;
}

int main()
{
	int z = 8;
	f(z);
	std::cout << z << std::endl;
}