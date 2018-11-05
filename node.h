#ifndef	_RPG_H
#define	_RPG_H	1

#include "ansics.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node* Node;
struct Node
{
	char	*data;
	Node	next;
	Node	prev;
	Node	parent;
	Node	children;
};

Node	newNode(char *data);

void	newChildren(Node n, char *data);

void	freeNode(Node n);

void	freeTree(Node n);

int	totalNode(Node n);

void	printNode(Node n);

void	clear();

#endif /* rpg.h */
