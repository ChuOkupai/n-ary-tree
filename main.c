#include "node.h"

void	exampleA()
{
	/*
	 *    o
	 *   / \
	 *  o   o
	 */
	Node n;
	
	n = newNode("parent");
	newChildren(n, "child1");
	newChildren(n, "child2");
	printf("n:\n");
	printNode(n);
	printf("n->children:\n");
	printNode(n->children);
	printf("n->children->next:\n");
	printNode(n->children->next);
	freeTree(n);
}

void	exampleB()
{
	/*
	 *     o  
	 *   / |
	 *  o  o
	 *   / | \
	 *  o  o  o
	 *    /  / \
	 *   o  o   o
	 */
	Node n;
	
	n = newNode("parent");
	newChildren(n, "child1-1");
	newChildren(n, "child1-2");
	newChildren(n->children->next, "child2-1");
	newChildren(n->children->next, "child2-2");
	newChildren(n->children->next, "child2-3");
	newChildren(n->children->next->children->next, "child3-1");
	newChildren(n->children->next->children->next->next, "child4-1");
	newChildren(n->children->next->children->next->next, "child4-2");
	printf("n:\n");
	printNode(n);
	printf("n->children->next:\n");
	printNode(n->children->next);
	printf("total nodes: %d\n", totalNode(n));
	freeTree(n);
}

int	main()
{
	printf("Example A:\n");
	exampleA();
	printf("\nExample B:\n");
	exampleB();
	return 0;
}
