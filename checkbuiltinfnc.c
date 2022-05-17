#include "shell.h"

/**
* checkbuiltinfnc - checks if the command is a builtin
* @arv: array of arguments
* Return: pointer to function that takes arv and returns void
*/
void(*checkbuiltinfnc(char **arv))(char **arv)
{
	int i, j;
	mybuild T[] = {
		{"exit", exitshell},
		{"env", print_env},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", _cd},
		{NULL, NULL}
	};

	printf("0");
	for (i = 0; T[i].name; i++)
	{
		printf("1");
		j = 0;
		if (T[i].name[j] == arv[0][j])
		{
			printf("2");
			for (j = 0; arv[0][j]; j++)
			{
				printf("3");
				if (T[i].name[j] != arv[0][j])
				{
					printf("4");
					break;
				}
			}
			printf("5");
			if (!arv[0][j])
			{
				printf("6");
				return (T[i].func);
			}
		}
	}
	return (0);
}
