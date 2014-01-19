//C++ Smart pointers
#include <iostream>

struct node
{
	int i;
	node * next;
};

template <class T>
class smartptr
{
private:
	T * ptr;
public:
	smartptr(T * t) { ptr = t; }
	~smartptr() { delete ptr; }
	T* operator ->() { return ptr; }
};

int main()
{
	smartptr<node> n(new node());
	n->next = NULL;
}