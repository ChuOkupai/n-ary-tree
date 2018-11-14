#include "node.h"
#include <stdio.h>
#include <string.h>

/* Print a node */
void	printNode(char *name, Node n)
{
	printf(" \e[4m%s:\e[0m\n", name);
	if (! n)
	{
		printf("  empty!\n");
		return;
	}
	Node o;
	int i;
	
	printf("  data     = ");
	if (n->data)
		printf("%s", (char*)n->data);
	else
		printf("false");
	printf("\n  next     = ");
	if (n->next)
	{
		for (i = 0, o = n; o->next; i++)
			o = o->next;
		printf("%d", i);
	}
	else
		printf("false");
	printf("\n  prev     = ");
	if (n->prev)
	{
		for (i = 0, o = n; o->prev; i++)
			o = o->prev;
		printf("%d", i);
	}
	else
		printf("false");
	printf("\n  parent   = %s", (n->parent) ? "true" : "false");
	printf("\n  children = ");
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

/* Compare 2 data elements (char*) */
int compare(void const *a, void const *b)
{
	return strcmp((char const*)a, (char const*)b);
}

void	exampleA()
{
	printf("\e[4mExample A:\e[0m\n");
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
	printNode("n", n);
	printNode("n->children", n->children);
	printNode("n->children->next", n->children->next);
	printf(" \e[4mtotal:\e[0m %d\n", getTotalNode(n));
	n = freeTree(n);
}

void	exampleB()
{
	printf("\e[4mExample B:\e[0m\n");
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
		newChildren(n->children->next->children->next->nextmake clean
		) ||
		newChildren(n->children->next->children->next->next, "child4-2"))
		n = freeTree(n);
	if (! n)
	{
		printf("Error during tree initialization!\n");
		return;
	}
	printNode("n", n);
	printNode("n->children->next", n->children->next);
	printf(" \e[4mtotal:\e[0m %d\n", getTotalNode(n));
	n = freeTree(n);
}

void	exampleC()
{
	printf("\e[4mExample C:\e[0m\n");
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
		newChildren(searchNode(n, "child1-1", compare), "child2-1"))
		n = freeTree(n);
	if (! n)
	{
		printf("Error during tree initialization!\n");
		return;
	}
	printNode("n", n);
	printNode("n->children", n->children);
	printNode("n->children->children", n->children->children);
	printf(" \e[4mtotal:\e[0m %d\n", getTotalNode(n));
	n = freeTree(n);
}

int	main()
{
	exampleA();
	putchar('\n');
	exampleB();
	putchar('\n');
	exampleC();
	return 0;
}