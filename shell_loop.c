#include "main.h"

/**
 * uncommented - deletes comments from the inp
 *
 * @in: inp string
 * Return: inp without comments
 */
char *uncommented(char *in)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		in = _realloc(in, i, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * terminal_loop - Loop of shell
 * @datashell: data relevant (argve, inp, args)
 *
 * Return: no return.
 */
void terminal_loop(shell_data *datashell)
{
	int loop, i_eof;
	char *inp;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "#cisfun$ ", 9);
		inp = read_line(&i_eof);
		if (i_eof != -1)
		{
			inp = uncommented(inp);
			if (inp == NULL)
				continue;

			if (error_check_syntax(datashell, inp) == 1)
			{
				datashell->status = 2;
				free(inp);
				continue;
			}
			inp = rep_var(inp, datashell);
			loop = split_commands(datashell, inp);
			datashell->counter += 1;
			free(inp);
		}
		else
		{
			loop = 0;
			free(inp);
		}
	}
}
