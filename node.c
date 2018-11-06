#include "node.h"

Node	newNode(char *data)
{
	Node n;
	
	n = NULL;
	n = (Node)malloc(sizeof(struct Node));
	if (! n)
		return n;
	n->data = data;
	n->next = NULL;
	n->prev = NULL;
	n->parent = NULL;
	n->children = NULL;
	return n;
}

void	newChildren(Node n, char *data)
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

Node	searchNode(Node n, char *data)
{
	if (! n)
		return n;
	if (n->data == data)
		return n;
	if (n->children)
		return searchNode(n->children, data);
	if (n->next)
		return searchNode(n->next, data);
	return NULL;
}

Node	freeNode(Node n)
{
	if (! n)
		return n;
	free(n);
	return NULL;
}

Node	freeTree(Node n)
{
	if (! n)
		return n;
	if (n->children)
		freeTree(n->children);
	if (n->next)
		freeTree(n->next);
	return freeNode(n);
}

int	totalNode(Node n)
{
	if (! n)
		return 0;
	int t;
	
	t = 0;
	if (n->children)
		t += totalNode(n->children);
	if (n->next)
		t += totalNode(n->next);
	return 1 + t;
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
