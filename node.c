#include "node.h"

Node	newNode(void *data)
{
	Node n;
	
	n = NULL;
	n = (Node)malloc(sizeof(struct Node));
	if (! n)
		return NULL;
	n->data = data;
	n->next = NULL;
	n->prev = NULL;
	n->parent = NULL;
	n->children = NULL;
	return n;
}

/*Node	newChildren(Node n, void *data)
{
	
}*/

void	freeNode(Node n)
{
	if (! n)
		return;
	free(n);
}

void	printNode(Node n)
{
	if (! n)
	{
		printf("Node is empty!\n");
		return;
	}
	Node o;
	int i;
	
	printf("Node->data = %s\n", (n->data) ? "true" : "false");
	printf("Node->next = ");
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
	printf("\nNode->parent = ");
	if (n->parent)
	{
		for (i = 0, o = n; o->parent; i++)
			o = o->parent;
		printf("%d", i);
	}
	else
		printf("false");
	putchar('\n');
	printf("Node->children = ");
	if (n->children)
	{
		for (i = 0, o = n; o->children; i++)
			o = o->children;
		printf("%d", i);
	}
	else
		printf("false");
	putchar('\n');
}

void	clear()
{
	printf("\033c");
}
