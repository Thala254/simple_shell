#include "main.h"

/**
 * exit_shell - exits the shell
 *
 * @datashell: data relevant (status and args)
 * Return: 0 on success.
 */
int exit_shell(shell_data *datashell)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int big_number;

	if (datashell->args[1] != NULL)
	{
		ustatus = _atoi(datashell->args[1]);
		is_digit = _isdigit(datashell->args[1]);
		str_len = _strlen(datashell->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			get_error(datashell, 2);
			datashell->status = 2;
			return (1);
		}
		datashell->status = (ustatus % 256);
	}
	return (0);
}
