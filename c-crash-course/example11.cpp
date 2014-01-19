//C++
#include <iostream>

class A
{
public:
	A() { std::cout << "Default ctor" << endl; }
	A(int i) { std::cout << "Non default ctor" << endl; }
	~A() { std::cout << "dtor" << endl; }
	void f() { std::cout << "woof" << std::endl; }
};

int main()
{
	A a;
	A b(1);
	a.f();
	d.f();
}