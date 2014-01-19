//Linked lists in C
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int i;
	struct node * next;
} node;

int main()
{
	node * root = malloc(sizeof(node));
	root->next = NULL;
	free(root);
	return 0;
}