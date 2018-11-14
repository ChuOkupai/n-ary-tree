#ifndef	_NODE_H
#define	_NODE_H	1

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

/* Create a new node */
Node	newNode(void *data);

/* Create a new children if node exist */
/** return a positive value on error **/
int	newChildren(Node n, void *data);

/* Create a new parent if node exist without parent */
int	newParent(Node n, void *data);

/* Search a node starting from a node */
/** If node don't exist, return NULL **/
Node	searchNode(Node n, void const *data, int (*compare)(void const *a, void const *b));

/* Get the root node in a tree (the first parent) */
Node	getNodeRoot(Node n);

/* Get the first child of node or NULL */
Node	getFirstChild(Node n);

/* Get the last child of node or NULL */
Node	getLastChild(Node n);

/* Return the number of children of a node */
int	getTotalChildren(Node n);

/* Return the number of nodes in a tree */
int	getTotalNode(Node n);

/* Free a node */
/** Return a NULL pointer **/
Node	freeNode(Node n);

/* Free a tree from node */
/** Return a NULL pointer **/
Node	freeTree(Node n);

#endif /* node.h */