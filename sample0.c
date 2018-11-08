#include "node.h"
#include <stdio.h>
#include <string.h>

int	fstrlen(FILE *f)
{
	int n;
	int c;
	
	n = 0;
	for (c = fgetc(f); c != '"' && c != EOF; c = fgetc(f))
		n++;
	fseek(f, -n - 1, SEEK_CUR);
	return n;
}

char*	fgetdata(FILE *f)
{
	char	*s;
	int		l;
	int		c;
	
	l = fstrlen(f);
	s = malloc(sizeof(char) * (l + 1));
	if (! s)
		return s;
	s[l] = '\0';
	c = fgetc(f);
	for (int i = 0; i < c && c != '"' && c != EOF; i++)
	{
		s[i] = c;
		c = fgetc(f);
	}
	return s;
}

Node	loadTree(char const *file)
{
	FILE	*f;
	Node	n;
	Node	r;
	char	c;
	
	f = NULL;
	n = NULL;
	r = NULL;
	f = fopen(file, "r");
	if (! f)
		return r;
	for (c = fgetc(f); c != EOF; c = fgetc(f))
	{
		if (c == '"')
		{
			if (! r)
			{
				r = newNode(fgetdata(f));
				n = r;
				if (! r)
					return r;
			}
			else
			{
				if (newChildren(n, fgetdata(f)))
				{
					fclose(f);
					r = freeTree(r);
					return r;
				}
				else
					n = getLastChild(n);
			}
		}
		else if (c == '.' && n->parent)
			n = n->parent;
	}
	fclose(f);
	return r;
}

void	checkNode(Node n)
{
	if (! n)
		return;
	if (n->children)
		checkNode(n->children);
	if (n->next)
		checkNode(n->next);
	char *s;
	
	s = n->data;
	printf("%s\n", s);
}

int	main()
{
	Node n;
	
	n = loadTree("sample0.tree");
	putchar('\n');
	if (! n)
	{
		printf("Error during tree initialization!\n");
		return 1;
	}
	checkNode(n);
	return 0;
}
