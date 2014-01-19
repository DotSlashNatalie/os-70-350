//C++ built in smart pointers
#include <iostream>
#include <memory>

using namespace std;

int main()
{
	shared_ptr<int> x(new int(5));
	unique_ptr<int> y(new int(10));
	shared_ptr<int> z = x;
	unique_ptr<int> yy = move(y);
}