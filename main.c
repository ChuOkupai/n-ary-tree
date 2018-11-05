#include "node.h"

int	main()
{
	Node n;
	char *a = "parent";
	char *b = "child1";
	char *c = "child2";
	
	n = newNode(a);
	newChildren(n, b);
	newChildren(n, c);
	printf("n:\n");
	printNode(n);
	printf("n->children:\n");
	printNode(n->children);
	printf("n->children->next:\n");
	printNode(n->children->next);
	freeNode(n->children->next);
	freeNode(n->children);
	freeNode(n);
	return 0;
}
