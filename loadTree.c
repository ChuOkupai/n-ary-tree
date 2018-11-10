#include "node.h"
#include <stdio.h>
#include <string.h>

#define ERROR_OPEN	1
#define ERROR_LOAD	2
#define ERROR_SYNT	3
int err;

int	fstrlen(FILE *f)
{
	if (! f)
	{
		err = ERROR_LOAD;
		return 0;
	}
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
	if (! f)
		return NULL;
	char	*s;
	int		l;
	int		c;
	
	l = fstrlen(f);
	s = malloc(sizeof(char) * (l + 1));
	if (! s)
	{
		err = ERROR_LOAD;
		return s;
	}
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
	char	*data;
	char	c;
	
	err = 0;
	f = NULL;
	n = NULL;
	r = NULL;
	f = fopen(file, "r");
	if (! f)
	{
		err = ERROR_OPEN;
		return r;
	}
	for (c = fgetc(f); ! err && c != EOF; c = fgetc(f))
	{
		if (c == '"')
		{
			data = fgetdata(f);
			if (! r && data)
			{
				r = newNode(data);
				n = r;
				if (! r)
					err = ERROR_LOAD;
			}
			else if (data)
			{
				if (newChildren(n, data))
					err = ERROR_LOAD;
				else
					n = getLastChild(n);
			}
		}
		else if (c == '.')
		{
			if (n->parent)
				n = n->parent;
			else
				err = ERROR_SYNT;
		}
		if (err)
		{
			fclose(f);
			r = freeTree(r);
			return r;
		}
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

int	main(int argc, char **argv)
{
	Node n;
	
	for (int i = 1; i < argc; i++)
	{
		n = NULL;
		n = loadTree(argv[i]);
		if (! n)
		{
			printf("%s: %s: ", argv[0], argv[i]);
			if (err == ERROR_OPEN)
				puts("No such file or directory");
			else if (err == ERROR_LOAD)
				puts("Could not load tree");
			else // err == ERROR_SYNT
				puts("Syntax error");
		}
		checkNode(n);
		n = freeTree(n);
	}
	return 0;
}
