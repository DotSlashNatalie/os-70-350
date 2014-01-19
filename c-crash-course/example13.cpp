//Linked lists in C++
#include <iostream>

struct node
{
	int i;
	node * next;
};

int main()
{
	node * root = new node();
	root->next = NULL;
	delete root;
	return 0;
}