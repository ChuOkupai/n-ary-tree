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

Data*	dataNew(char *answer, char *dialog)
{
	Data	*data;
	
	data = NULL;
	data = malloc(sizeof(Data*));
	if (data)
	{
		data->answer = answer;
		data->dialog = dialog;
	}
	else
		err = ERR_LOAD;
	return data;
}

/* strlen for string in file */
int	dataLen(FILE *file)
{
	if (! file)
	{
		err = ERR_LOAD;
		return 0;
	}
	int		len;
	int		c;
	
	len = 0;
	for (c = fgetc(file); c != '"' && c != EOF; c = fgetc(file))
		len++;
	if (! len || c == EOF)
		err = ERR_SYNT;
	fseek(file, -len - 1, SEEK_CUR);
	return len + 1;
}

/* return string from file */
char*	dataGrep(FILE *file)
{
	if (! file)
	{
		err = ERR_LOAD;
		return NULL;
	}
	char	*str;
	int		len;
	
	str = NULL;
	len = dataLen(file);
	if (err)
		return str;
	str = malloc(len + 1);
	if (! str)
	{
		err = ERR_LOAD;
		return str;
	}
	for (int i = 0; i < len; i++)
		str[i] = fgetc(file);
	str[len - 1] = '\0';
	return str;
}

Node*	loadTree(char const *filename)
{
	FILE	*file;
	Node	*root;
	Node	*node;
	int		answer;
	int		comment;
	int		c;
	
	root = NULL;
	node = NULL;
	answer = 0;
	comment = 0;
	file = fopen(filename, "r");
	if (! file)
		err = ERR_OPEN;
	for (c = 0; c != EOF; c = fgetc(file))
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
					((Data*)node->data)->answer = dataGrep(file);
					if (! ((Data*)node->data)->answer)
						err = ERR_OPEN;
					answer = 0;
				}
				else 
				{
					node = nodeAppend(node, nodeNew(dataNew(NULL, dataGrep(file))));
					if (! node)
						err = ERR_OPEN;
				}
			}
			else
			{
				root = nodeNew(dataNew(NULL, dataGrep(file)));
				if (root)
					node = root;
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
			if (! answer && root && node->parent)
				node = node->parent;
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
	if (file)
		fclose(file);
	return root;
}

void	nodePrint(Node *node)
{
	if (! node)
		return;
	Node *root;
	
	root = node;
	if (((Data*)node->data)->dialog)
		printf("%s\n", ((Data*)node->data)->dialog);
	if (node->children)
	{
		node = node->children;
		for (int i = 0; node; i++)
		{
			if (((Data*)node->data)->answer)
				printf(" > %d: %s\n", i, ((Data*)node->data)->answer);
			node = node->next;
		}
	}
	if (root->children)
		nodePrint(root->children);
	if (root->next)
		nodePrint(root->next);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
		printf("%s: missing file operand\nTry '%s --help' for more information\n", argv[0], argv[0]);
	Node	*node;
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
		node = NULL;
		node = loadTree(argv[i]);
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
			nodePrint(node);
		nodeDestroy(node);
	}
	return 0;
}