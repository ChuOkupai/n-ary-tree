#include "node.h"

Node	newNode(void *data)
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

int	newChildren(Node n, void *data)
{
	if (! n)
	{
		n = newNode(data);
		if (! n)
			return 1;
		return 0;
	}
	if (! n->children)
	{
		n->children = newNode(data);
		if (! n->children)
			return 2;
		n->children->parent = n;
		return 0;
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
	if (! p->next)
		return 3;
	p->next->prev = o;
	p->next->parent = p->parent;
	return 0;
}

int	newParent(Node n, void *data)
{
	if (! n)
		return 1;
	if (n->parent)
		return 2;
	
	n->parent = newNode(data);
	if (! n->parent)
		return 3;
	n->parent->children = n;
	return 0;
}

Node	searchNode(Node root, void const *data, int (*compare)(void const *a, void const *b))
{
	if (! root)
		return root;
	if (! compare(data, root->data))
		return root;
	if (root->next)
		return searchNode(root->next, data, compare);
	if (root->children)
		return searchNode(root->children, data, compare);
	return NULL;
}

Node	getNodeRoot(Node n)
{
	if (! n)
		return n;
	if (n->parent)
		return getNodeRoot(n->parent);
	return n;
}

Node	getFirstChild(Node n)
{
	if (! n)
		return n;
	if (n->children)
		return n->children;
	return NULL;
}

Node	getLastChild(Node n)
{
	if (! n)
		return n;
	if (! n->children)
		return NULL;
	n = n->children;
	while (n->next)
		n = n->next;
	return n;
}

int	getTotalChildren(Node n)
{
	if (! n)
		return 0;
	if (! n->children)
		return 0;
	int t;
	
	n = n->children;
	for (t = 1; n->next; t++)
		n = n->next;
	return t;
}

int	getTotalNode(Node root)
{
	if (! root)
		return 0;
	int t;
	
	t = 0;
	if (root->children)
		t += getTotalNode(root->children);
	if (root->next)
		t += getTotalNode(root->next);
	return 1 + t;
}

Node	freeNode(Node n)
{
	if (! n)
		return n;
	free(n);
	return NULL;
}

Node	freeTree(Node root)
{
	if (! root)
		return root;
	if (root->children)
		freeTree(root->children);
	if (root->next)
		freeTree(root->next);
	return freeNode(root);
}
