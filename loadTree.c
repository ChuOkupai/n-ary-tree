#include "node.h"
#include <stdio.h>
#include <string.h>

#define ERR_OPEN	-1
#define ERR_LOAD	-2
#define ERR_SYNT	-3
#define ERR_EMPTY	-4
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

/* strlen for string in file */
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

/* return string from file */
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
	return s;
}

Node	loadTree(char const *filename)
{
	FILE	*f;
	Node	root;
	Node	n;
	int		answer;
	int		comment;
	int		c;
	
	f = NULL;
	root = NULL;
	n = NULL;
	answer = 0;
	comment = 0;
	f = fopen(filename, "r");
	if (! f)
		err = ERR_OPEN;
	for (c = 0; c != EOF; c = fgetc(f))
	{
		if (c == '#' || (comment && c == '\n')) // Check for comment
			comment = 1 - comment;
		else if (comment); // Do nothing if comment
		else if (c == '"') // Add a new string
		{
			if (root)
			{
				if (answer)
				{
					((Data*)n->data)->answer = fdatagrep(f);
					if (! ((Data*)n->data)->answer)
						err = ERR_OPEN;
					answer = 0;
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
				root = newNode(newData(NULL, fdatagrep(f)));
				if (root)
					n = root;
				else
					err = ERR_OPEN;
			}
		}
		else if (c == ',') //  Next string is an answer
		{
			if (! answer && root)
				answer = 1;
			else
				err = ERR_SYNT;
		}
		else if (c == '^') // Return to parent
		{
			if (! answer && root && n->parent)
				n = n->parent;
			else
				err = ERR_SYNT;
		}
		if (err)
			break;
	}
	if (answer)
		err = ERR_SYNT;
	if (! (err || root))
		err = ERR_EMPTY;
	if (f)
		fclose(f);
	return root;
}

void	printNode(Node n)
{
	if (! n)
		return;
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
		printNode(r->children);
	if (r->next)
		printNode(r->next);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
		printf("%s: missing file operand\nTry '%s --help' for more information\n", argv[0], argv[0]);
	Node	n;
	int i;
	
	for (i = 1; i < argc; i++)
	{
		// Check for help flag
		if (! strcmp(argv[i], "--help"))
		{
			printf("Usage: %s [FILE]...\n", argv[0]);
			printf("Load and print tree FILE(s) to standard output.\n\n");
			printf("Example:\n  %s sample.tree  Output loaded sample.tree's content\n", argv[0]);
			argc = 1;
		}
	}
	for (int i = 1; i < argc; i++)
	{
		// Load file and display tree's content is there is no error
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
			else if (err == ERR_SYNT)
				puts("Syntax error");
			else // err == ERR_EMPTY
				puts("Tree is empty");
		}
		else
			printNode(n);
		n = freeTree(n);
		
	}
	return 0;
}