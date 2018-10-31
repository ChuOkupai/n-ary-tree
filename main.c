#include "rpg.h"

CHARACTER init_michel()
{
	CHARACTER C;
	
	C = newcharacter("Michel", newdialog("Bonjour", NULL, 0, 1));
	C.D->next[0] = newdialog("Vous allez bien ?", newanswer(2, "Oui", "Non"), 2, 2);
		C.D->next[0]->next[0] = newdialog("Tant mieux !", NULL, 0, 0);
	C.D->next[1] = newdialog("Oh... Pourquoi ?", newanswer(3, "Je suis fatigué...", "Je suis malade", "Heu... Hum... Je ne sais plus"), 3, 1);
		C.D->next[1]->next[0] = newdialog("Courage !", NULL, 0, 0);
	return C;
}

void	printdial(CHARACTER C)
{
	if (! C.D)
		return;
	int c;
	
	while (C.D)
	{
		clear();
		printf(ACS_F(UNDERLINED) "%s:" ACS_R "\n", C.name);
		printf(" %s\n", C.D->text);
		for (int i = 0; i < C.D->in; i++)
			printf("  %d:%s\n", i, C.D->answer[i]);
		c = -1;
		c = getchar() - 48;
		if (! C.D->out)
			C.D = NULL;
		else if (! C.D->in)
			C.D = C.D->next[0];
		else
		{
			while (c < C.D->in && c >= C.D->in)
				c = getchar() - 48;
			if (c < C.D->out)
				C.D = C.D->next[c - 48];
			else
				C.D = C.D->next[0];
		}
	}
}

int	main()
{
	CHARACTER M;
	
	M = init_michel();
	printdial(M);
	return 0;
}
