#include "shell.h"

/**
* get_cwd - gets the current working directory
*
* Return: string containing the current working directory
*/

char *get_cwd(void)
{
	size_t len = PATH_MAX;
	char *cwd;

	cwd = malloc(sizeof(char) * len);

	if (cwd == NULL)
	{
		perror("Error: Memory allocation cwd\n");
		return (NULL);
	}

	if (getcwd(cwd, len) == NULL)
	{
		free(cwd);
		perror("Error: getcwd->NULL\n");
		return (NULL);
	}

	return (cwd);
}

/**
* cd_home - handles cd if no argument is given
*
* Return: 0 on success
*/

int cd_home(void)
{
	char *cwd, *home;
	char **envv;

	cwd = get_cwd();

	envv = malloc(sizeof(char **) * 20);
	envv[0] = "OLDPWD";
	envv[1] = cwd;

	_setenv(envv);
	free(cwd);

	home = _getenv("HOME");
	chdir("home");
	free(home);

	cwd = get_cwd();
	envv[0] = "PWD";
	_setenv(envv);

	free(cwd);
	free(envv);

	return (0);
}

/**
* cd_prev - navigates to the previous directory when the user invokes cd-
*
* Return: 0 on success
*/

int cd_prev(void)
{
	char *cwd, *prev;
	char **envv;

	cwd = get_cwd();

	prev = _getenv("OLDPWD");
	chdir(prev);
	prev = NULL;

	envv = malloc(sizeof(char **) * 20);
	envv[0] = "OLDPWD";
	envv[1] = cwd;
	_setenv(envv);
	cwd = NULL;

	cwd = get_cwd();
	envv[0] = "PWD";
	_setenv(envv);
	free(cwd);

	return (0);
}

/**
* _cd - changes the current working directory
*
* @args: commands passed to cd
*
* Return: void
*/

void _cd(char **args)
{
	char *cwd;
	char **envv;

	if (args[1])
	{
		/* checking - for previous cd */
		if (strncmp(args[1], "-", 1) == 0)
		{
			cd_prev();
		}
		else
		{
			cwd = get_cwd();
			envv = malloc(sizeof(char **) * 20);
			envv[0] = "OLDPWD";
			envv[1] = cwd;
			_setenv(envv);
			free(cwd);

			if (chdir(args[1]) == -1)
			{
				perror("Error: chdir\n");
			}

			cwd = get_cwd();
			envv[0] = "PWD";
			_setenv(envv);
			free(cwd);
		}
	}
	/* no args in cd */
	else
	{
		cd_home();
	}
}
