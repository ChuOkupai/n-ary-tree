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

void	newChildren(Node n, void *data)
{
	if (! n)
		return;
	if (! n->children)
	{
		n->children = newNode(data);
		if (n->children)
			n->children->parent = n;
		return;
	}
	Node o, p;
	
	o = n;
	p = n->children;
	while (p->next)
	{
		o = p;
		p = p->next;
	}
	p->next = newNode(data);
	if (p->next)
	{
		p->next->prev = o;
		p->next->parent = p->parent;
	}
}

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
	if (n->data)
	{
		char *s = n->data;
		printf("Node->data = %s\n", s);
	}
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

void	clear()
{
	printf("\033c");
}
