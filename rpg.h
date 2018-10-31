#ifndef	_RPG_H
#define	_RPG_H	1

#include "ansics.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct dialog* DIALOG;
struct dialog
{
	char	*text;
	char	**answer;
	int		in;
	int		out;
	DIALOG	*next;
};

typedef struct character
{
	char	*name;
	DIALOG	D;
}	CHARACTER;

CHARACTER	newcharacter(char *name, DIALOG D);

DIALOG	newdialog(char *text, char **answer, int in, int out);

char** newanswer(int in, ...);

void	printdialog(CHARACTER C);

void	clear();

#endif /* rpg.h */
