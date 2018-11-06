#ifndef	_RPG_H
#define	_RPG_H	1

#include "ansics.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node* Node;
struct Node
{
	char	*data;
	Node	next;
	Node	prev;
	Node	parent;
	Node	children;
};

/* Create a new node */
Node	newNode(char *data);

/* Create a new children if node exist */
int	newChildren(Node n, char *data);

/* Search a node in a tree */
/** If node don't exist, return NULL **/
Node	searchNode(Node n, char *data);

/* Free a node */
Node	freeNode(Node n);

/* Free a tree */
Node	freeTree(Node n);

/* Return the number of nodes in a tree */
int	totalNode(Node n);

/* Print a node */
void	printNode(Node n);

#endif /* rpg.h */
