#include "node.h"
#include <stdio.h>
#include <string.h>

/* Print a node */
void	nodePrint(char *name, Node *n)
{
	printf(" \e[4m%s:\e[0m\n", name);
	if (! n)
	{
		printf("  empty!\n");
		return;
	}
	Node *o;
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
	Node *n;
	
	n = nodeNew("parent");
	if (! nodeAppend(n, nodeNew("child1")) ||
		! nodeAppend(n, nodeNew("child2")))
	{
		nodeDestroy(n);
		n = NULL;
	}
	if (! n)
	{
		printf("Error during tree initialization!\n");
		return;
	}
	nodePrint("n", n);
	nodePrint("n->children", n->children);
	nodePrint("n->children->next", n->children->next);
	printf(" \e[4mtotal:\e[0m %d\n", nodeTotal(n));
	nodeDestroy(n);
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
	Node *n;
	
	n = nodeNew("parent");
	if (! nodeAppend(n, nodeNew("child1-1")) ||
		! nodeAppend(n, nodeNew("child1-2")) ||
		! nodeAppend(n->children->next, nodeNew("child2-1")) ||
		! nodeAppend(n->children->next, nodeNew("child2-2")) ||
		! nodeAppend(n->children->next, nodeNew("child2-3")) ||
		! nodeAppend(n->children->next->children->next, nodeNew("child3-1")) ||
		! nodeAppend(n->children->next->children->next->next, nodeNew("child4-2")) ||
		! nodeAppend(n->children->next->children->next->next, nodeNew("child4-2")))
		nodeDestroy(n);
	if (! n)
	{
		printf("Error during tree initialization!\n");
		return;
	}
	nodePrint("n", n);
	nodePrint("n->children->next", n->children->next);
	printf(" \e[4mtotal:\e[0m %d\n", nodeTotal(n));
	nodeDestroy(n);
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
	Node *n;
	
	n = nodeNew("parent");
	if (! nodeAppend(n, nodeNew("child1-1")) ||
		! nodeAppend(n->children, nodeNew("child2-1")))
		nodeDestroy(n);
	if (! n)
	{
		printf("Error during tree initialization!\n");
		return;
	}
	nodePrint("n", n);
	nodePrint("n->children", n->children);
	nodePrint("n->children->children", n->children->children);
	printf(" \e[4mtotal:\e[0m %d\n", nodeTotal(n));
	nodeDestroy(n);
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