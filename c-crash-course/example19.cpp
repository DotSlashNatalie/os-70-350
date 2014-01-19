//C++ - using iterators
#include <vector>
#include <iostream>

void slice(std::vector<int>::iterator start, std::vector<int>::iterator end)
{
	for(std::vector<int>::iterator i = start; i != end; i++)
		std::cout << *i << std::endl;
}

int main()
{
	std::vector<int> x;
	for (int i= 0; i < 10; ++i) { x.push_back(i); }

	for(std::vector<int>::iterator i = x.begin(); i != x.end(); i++)
		std::cout << *i << std::endl;
	std::cout << std::endl;
	slice(x.begin(), x.begin() + 2);
	std::cout << std::endl;
	slice(x.end() - 2, x.end());
}