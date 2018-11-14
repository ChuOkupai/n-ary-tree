#include "node.h"
#include <stdio.h>

#define ERR_OPEN	-1
#define ERR_LOAD	-2
#define ERR_SYNT	-3
int err;

typedef struct Data
{
	char	*answer;
	char	*dialog;
}	Data;

Data*	newData(char *answer, char *dialog)
{
	Data	*d;
	
	d = NULL;
	d = malloc(sizeof(Data*));
	if (d)
	{
		d->answer = answer;
		d->dialog = dialog;
	}
	else
		err = ERR_LOAD;
	return d;
}

int	fdatalen(FILE *f)
{
	if (! f)
	{
		err = ERR_LOAD;
		return 0;
	}
	int		l;
	int		c;
	
	l = 0;
	for (c = fgetc(f); c != '"' && c != EOF; c = fgetc(f))
		l++;
	if (! l || c == EOF)
		err = ERR_SYNT;
	fseek(f, -l - 1, SEEK_CUR);
	return l + 1;
}

char*	fdatagrep(FILE *f)
{
	if (! f)
	{
		err = ERR_LOAD;
		return NULL;
	}
	char	*s;
	int		l;
	
	s = NULL;
	l = fdatalen(f);
	if (err)
		return s;
	s = malloc(l + 1);
	if (! s)
	{
		err = ERR_LOAD;
		return s;
	}
	for (int i = 0; i < l; i++)
		s[i] = fgetc(f);
	s[l - 1] = '\0';
	//printf("%s\n", s);
	return s;
}

Node	loadTree(char const *filename)
{
	FILE	*f;
	Node	r;
	Node	n;
	int		a;
	int		c;
	
	f = NULL;
	r = NULL;
	n = NULL;
	a = 0;
	f = fopen(filename, "r");
	if (! f)
		err = ERR_OPEN;
	for (c = 0; c != EOF; c = fgetc(f))
	{
		if (c == '"')
		{
			if (r)
			{
				if (a)
				{
					((Data*)n->data)->answer = fdatagrep(f);
					if (! ((Data*)n->data)->answer)
						err = ERR_OPEN;
					a = 0;
				}
				else 
				{
					if (newChildren(n, newData(NULL, fdatagrep(f))))
						err = ERR_OPEN;
					else
						n = getLastChild(n);
				}
			}
			else
			{
				r = newNode(newData(NULL, fdatagrep(f)));
				if (r)
					n = r;
				else
					err = ERR_OPEN;
			}
		}
		else if (c == ',')
		{
			if (! a && r)
				a = 1;
			else
				err = ERR_SYNT;
		}
		else if (c == '^')
		{
			if ((a || ! n->parent) && r)
				err = ERR_SYNT;
			else
				n = n->parent;
		}
		if (err)
			break;
	}
	if (f)
		fclose(f);
	return r;
}

void	checkNode(Node n)
{
	if (! n)
	{
		printf("empty!\n");
		return;
	}
	Node r;
	
	r = n;
	if (((Data*)n->data)->dialog)
		printf("%s\n", ((Data*)n->data)->dialog);
	if (n->children)
	{
		n = n->children;
		for (int i = 0; n; i++)
		{
			if (((Data*)n->data)->answer)
				printf(" > %d: %s\n", i, ((Data*)n->data)->answer);
			n = n->next;
		}
	}
	if (r->children)
		checkNode(r->children);
	if (r->next)
		checkNode(r->next);
}

int	main(int argc, char **argv)
{
	Node	n;
	
	for (int i = 1; i < argc; i++)
	{
		err = 0;
		n = NULL;
		n = loadTree(argv[i]);
		if (err)
		{
			printf("%s: %s: ", argv[0], argv[i]);
			if (err == ERR_OPEN)
				puts("No such file or directory");
			else if (err == ERR_LOAD)
				puts("Could not load tree");
			else // err == ERR_SYNT
				puts("Syntax error");
		}
		checkNode(n);
		n = freeTree(n);
		
	}
	return 0;
}