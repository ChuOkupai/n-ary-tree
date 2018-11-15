#ifndef	_NODE_H
#define	_NODE_H	1

#include <stdlib.h>

typedef struct Node Node;
struct Node
{
	void	*data;
	Node	*next;
	Node	*prev;
	Node	*parent;
	Node	*children;
};

/* Creates a new Node containing the given data */
/** Returns NULL on error **/
Node*	nodeNew(void *data);

/* Inserts a Node as the first child of the given parent */
/** Returns NULL on error **/
#define	nodePrepend(parent, node)	nodeInsertBefore((Node*)parent, (Node*)parent->children, (Node*)node)

/* Inserts a Node as the last child of the given parent */
/** Returns NULL on error **/
#define	nodeAppend(parent, node)	nodeInsertBefore((Node*)parent, NULL, (Node*)node)

/* Inserts a Node beneath the parent at the given position */
/** Returns NULL on error **/
Node*	nodeInsert(Node *parent, int position, Node *node);

/* Inserts a Node beneath the parent after the given sibling */
Node*	nodeInsertAfter(Node *parent, Node *sibling, Node *node);

/* Inserts a Node beneath the parent before the given sibling */
/** If sibling is NULL, the node is inserted as the last child of parent **/
/** Returns NULL on error **/
Node*	nodeInsertBefore(Node *parent, Node *sibling, Node *node);

/* Returns a positive value if a Node is the root of a tree else 0 */
#define	nodeIsRoot(node)	(! ((Node*)(node))->parent && ! ((Node*)(node))->next)

/* Gets the root of a tree */
/** Returns NULL on error **/
Node*	nodeRoot(Node *node);

/* Finds a Node in a tree */
Node*	nodeFind(Node *node, void *data, int (*compare)(void *a, void *b));

/* Gets a child of a Node, using the given index */
/** Returns NULL if the index is too big **/
Node*	nodeNthChild(Node *node, int n);

/* Gets the number of nodes in a tree */
int	nodeTotal(Node	*root);

/* Unlinks a Node from a tree, resulting in two separate trees */
void	nodeUnlink(Node *node);

/* Removes root and its children from the tree, freeing any memory allocated */
void	nodeDestroy(Node *root);

#endif /* node.h */