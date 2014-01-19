//By default values are passed by value (or copy)
#include <iostream>

void f(int i)
{
	i = 4;
}

int main()
{
	int x = 10;
	f(x);
	std::cout << x << std::endl;
	return 0;
}