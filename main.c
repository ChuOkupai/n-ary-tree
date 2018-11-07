#include "node.h"
#include <stdio.h>

/* Print a node */
void	printNode(Node n)
{
	if (! n)
	{
		printf("Node is empty!\n");
		return;
	}
	Node o;
	int i;
	
	printf("Node->data = ");
	if (n->data)
		printf("%s", n->data);
	else
		printf("false");
	printf("\nNode->next = ");
	if (n->next)
	{
		for (i = 0, o = n; o->next; i++)
			o = o->next;
		printf("%d", i);
	}
	else
		printf("false");
	printf("\nNode->prev = ");
	if (n->prev)
	{
		for (i = 0, o = n; o->prev; i++)
			o = o->prev;
		printf("%d", i);
	}
	else
		printf("false");
	printf("\nNode->parent = %s", (n->parent) ? "true" : "false");
	printf("\nNode->children = ");
	if (n->children)
	{
		for (i = 0, o = n->children; o; i++)
			o = o->next;
		printf("%d", i);
	}
	else
		printf("false");
	putchar('\n');
}

void	exampleA()
{
	/*
	 *    o
	 *   / \
	 *  o   o
	 */
	Node n;
	
	n = newNode("parent");
	if (newChildren(n, "child1") ||
		newChildren(n, "child2"))
		n = freeTree(n);
	if (! n)
	{
		printf("Error during tree initialization!\n");
		return;
	}
	printf("n:\n");
	printNode(n);
	printf("n->children:\n");
	printNode(n->children);
	printf("n->children->next:\n");
	printNode(n->children->next);
	printf("total nodes: %d\n", getTotalNode(n));
	n = freeTree(n);
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
	if (newChildren(n, "child1-1") ||
		newChildren(n, "child1-2") ||
		newChildren(n->children->next, "child2-1") ||
		newChildren(n->children->next, "child2-2") ||
		newChildren(n->children->next, "child2-3") ||
		newChildren(n->children->next->children->next, "child3-1") ||
		newChildren(n->children->next->children->next->next, "child4-1") ||
		newChildren(n->children->next->children->next->next, "child4-2"))
		n = freeTree(n);
	if (! n)
	{
		printf("Error during tree initialization!\n");
		return;
	}
	printf("n:\n");
	printNode(n);
	printf("n->children->next:\n");
	printNode(n->children->next);
	printf("total nodes: %d\n", getTotalNode(n));
	n = freeTree(n);
}

void	exampleC()
{
	/*
	 *    o
	 *   /
	 *  o
	 *  |
	 *  o
	 */
	Node n;
	
	n = newNode("parent");
	if (newChildren(n, "child1-1") ||
		newChildren(searchNode(n, "child1-1"), "child2-1"))
		n = freeTree(n);
	if (! n)
	{
		printf("Error during tree initialization!\n");
		return;
	}
	printf("n:\n");
	printNode(n);
	printf("n->children:\n");
	printNode(n->children);
	printf("n->children->children:\n");
	printNode(n->children->children);
	printf("total nodes: %d\n", getTotalNode(n));
	n = freeTree(n);
}

int	main()
{
	printf("Example A:\n");
	exampleA();
	printf("\nExample B:\n");
	exampleB();
	printf("\nExample C:\n");
	exampleC();
	return 0;
}
