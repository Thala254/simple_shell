#include "main.h"

/**
 * char_repeated - counts the repetitions of a char
 *
 * @inp: inp string
 * @i: index
 * Return: repetitions
 */
int char_repeated(char *inp, int i)
{
	if (*(inp - 1) == *inp)
		return (char_repeated(inp - 1, i + 1));

	return (i);
}

/**
 * err_sep - finds syntax errors
 *
 * @inp: inp string
 * @i: index
 * @last: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int err_sep(char *inp, int i, char last)
{
	int count;

	count = 0;
	if (*inp == '\0')
		return (0);

	if (*inp == ' ' || *inp == '\t')
		return (err_sep(inp + 1, i + 1, last));

	if (*inp == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*inp == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = char_repeated(inp, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*inp == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = char_repeated(inp, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (err_sep(inp + 1, i + 1, *inp));
}

/**
 * first_char - finds index of the first char
 *
 * @inp: inp string
 * @i: index
 * Return: 1 if there is an error. 0 in other case.
 */
int first_char(char *inp, int *i)
{

	for (*i = 0; inp[*i]; *i += 1)
	{
		if (inp[*i] == ' ' || inp[*i] == '\t')
			continue;

		if (inp[*i] == ';' || inp[*i] == '|' || inp[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * err_print_syntax - prints when a syntax error is found
 *
 * @datashell: data structure
 * @inp: inp string
 * @i: index of the error
 * @bool: to control msg error
 * Return: no return
 */
void err_print_syntax(shell_data *datashell, char *inp, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (inp[i] == ';')
	{
		if (bool == 0)
			msg = (inp[i + 1] == ';' ? ";;" : ";");
		else
			msg = (inp[i - 1] == ';' ? ";;" : ";");
	}

	if (inp[i] == '|')
		msg = (inp[i + 1] == '|' ? "||" : "|");

	if (inp[i] == '&')
		msg = (inp[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = aux_itoa(datashell->counter);
	length = _strlen(datashell->argve[0]) + _strlen(counter);
	length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, datashell->argve[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * error_check_syntax - intermediate function to
 * find and print a syntax error
 *
 * @datashell: data structure
 * @inp: inp string
 * Return: 1 if there is an error. 0 in other case
 */
int error_check_syntax(shell_data *datashell, char *inp)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = first_char(inp, &begin);
	if (f_char == -1)
	{
		err_print_syntax(datashell, inp, begin, 0);
		return (1);
	}

	i = err_sep(inp + begin, 0, *(inp + begin));
	if (i != 0)
	{
		err_print_syntax(datashell, inp, begin + i, 1);
		return (1);
	}

	return (0);
}
