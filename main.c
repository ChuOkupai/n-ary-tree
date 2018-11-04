#include "node.h"

int	main()
{
	Node n;
	int a;
	
	a = 42;
	n = newNode(&a);
	n->children = newNode(0);
	n->children->children = newNode(0);
	printNode(n);
	freeNode(n->children->children);
	freeNode(n->children);
	freeNode(n);
	return 0;
}
