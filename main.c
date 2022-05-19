#include "main.h"

/**
 * free_data - frees data structure
 *
 * @datashell: data structure
 * Return: no return
 */
void free_data(shell_data *datashell)
{
	unsigned int i;

	for (i = 0; datashell->_environ[i]; i++)
	{
		free(datashell->_environ[i]);
	}

	free(datashell->_environ);
	free(datashell->pid);
}

/**
 * set_data - Initialize data structure
 *
 * @datashell: data structure
 * @argve: argument vector
 * Return: no return
 */
void set_data(shell_data *datashell, char **argve)
{
	unsigned int i;

	datashell->argve = argve;
	datashell->inp = NULL;
	datashell->args = NULL;
	datashell->status = 0;
	datashell->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	datashell->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		datashell->_environ[i] = _strdup(environ[i]);
	}

	datashell->_environ[i] = NULL;
	datashell->pid = aux_itoa(getpid());
}

/**
 * main - Entry point
 *
 * @ac: argument count
 * @argve: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **argve)
{
	shell_data datashell;
	(void) ac;

	signal(SIGINT, get_sigint);
	set_data(&datashell, argve);
	terminal_loop(&datashell);
	free_data(&datashell);
	if (datashell.status < 0)
		return (255);
	return (datashell.status);
}
