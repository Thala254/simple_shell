#include "main.h"

/**
 * swap_char - swaps | and & for non-printed chars
 *
 * @inp: inp string
 * @bool: type of swap
 * Return: swapped string
 */
char *swap_char(char *inp, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; inp[i]; i++)
		{
			if (inp[i] == '|')
			{
				if (inp[i + 1] != '|')
					inp[i] = 16;
				else
					i++;
			}

			if (inp[i] == '&')
			{
				if (inp[i + 1] != '&')
					inp[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; inp[i]; i++)
		{
			inp[i] = (inp[i] == 16 ? '|' : inp[i]);
			inp[i] = (inp[i] == 12 ? '&' : inp[i]);
		}
	}
	return (inp);
}

/**
 * add_nodes - add separators and command lines in the lists
 *
 * @head_s: head of separator list
 * @head_l: head of command lines list
 * @inp: inp string
 * Return: no return
 */
void add_nodes(list_sep **head_s, command_list **head_l, char *inp)
{
	int i;
	char *line;

	inp = swap_char(inp, 0);

	for (i = 0; inp[i]; i++)
	{
		if (inp[i] == ';')
			add_sep(head_s, inp[i]);

		if (inp[i] == '|' || inp[i] == '&')
		{
			add_sep(head_s, inp[i]);
			i++;
		}
	}

	line = _strtok(inp, ";|&");
	do {
		line = swap_char(line, 1);
		add_line(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * go_next - go to the next command line stored
 *
 * @list_s: separator list
 * @list_l: command line list
 * @datashell: data structure
 * Return: no return
 */
void go_next(list_sep **list_s, command_list **list_l, shell_data *datashell)
{
	int loop_sep;
	list_sep *ls_s;
	command_list *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (datashell->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * split_commands - splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @datashell: data structure
 * @inp: inp string
 * Return: 0 to exit, 1 to continue
 */
int split_commands(shell_data *datashell, char *inp)
{

	list_sep *head_s, *list_s;
	command_list *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	add_nodes(&head_s, &head_l, inp);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datashell->inp = list_l->line;
		datashell->args = split_line(datashell->inp);
		loop = exec_line(datashell);
		free(datashell->args);

		if (loop == 0)
			break;

		go_next(&list_s, &list_l, datashell);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_list_sep(&head_s);
	free_command_list(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * split_line - tokenizes the inp string
 *
 * @inp: inp string.
 * Return: string splitted.
 */
char **split_line(char *inp)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(inp, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}
