//C++ - using vectors as C arrays
#include <vector>
#include <iostream>

void f(int * arr, size_t count)
{
	for(size_t i = 0; i < count; i++)
		std::cout << *(i+arr) << std::endl; //arr[i] also works as well
}

int main()
{
	std::vector<int> x;
	x.push_back(1);
	x.push_back(2);
	f(&x[0], x.size());
	return 0;
}