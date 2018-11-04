#ifndef	_RPG_H
#define	_RPG_H	1

#include "ansics.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node* Node;
struct Node
{
	void	*data;
	Node	next;
	Node	prev;
	Node	parent;
	Node	children;
};

Node	newNode(void *data);

Node	newChildren(Node n, void *data);

void	freeNode(Node n);

void	printNode(Node n);

void	clear();

#endif /* rpg.h */
