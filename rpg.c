#include "rpg.h"

CHARACTER	newcharacter(char *name, DIALOG D)
{
	CHARACTER C;
	
	C.name = name;
	C.D = D;
	return C;
}

DIALOG	newdialog(char *text, char **answer, int in, int out)
{
	DIALOG D;
	
	D = malloc(sizeof(DIALOG));
	if (! D)
		return D;
	D->text = text;
	D->answer = answer;
	D->in = in;
	D->out = out;
	D->next = malloc(out * sizeof(DIALOG));
	return D;
}

char** newanswer(int in, ...)
{
	va_list	arg;
	char	**s;
	
	s = malloc(in * sizeof(char*));
	if (! s)
		return s;
	va_start(arg, in);
	for (int i = 0; i < in; i++)
		s[i] = va_arg(arg, char*);
	va_end(arg);
	return s;
}

void	printdialog(CHARACTER C)
{
	if (! C.D)
		return;
	int i, in;
	
	while (C.D)
	{
		clear();
		printf(ACS_F(UNDERLINED) "%s:" ACS_R "\n", C.name);
		printf(" %s\n", C.D->text);
		for (i = 0; i < C.D->in; i++)
			printf("  %d:%s\n", C.D->in, C.D->answer[i]);
		in = (in) ? -1 : 0;
		if (! in)
			getchar();
		else
			while (in < 0 && in >= C.D->in)
				if (scanf("%d", &in) == EOF)
				{
					in = 0;
					break;
				}
		if (C.D->in > C.D->out)
			in %= C.D->out;
		C.D = C.D->next[in];
	}
}

void	clear()
{
	printf("\033c");
}
