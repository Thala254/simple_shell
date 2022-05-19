#include "main.h"

/**
 * error_env - error message for env in get_env.
 * @datashell: data relevant (counter, arguments)
 * Return: error message.
 */
char *error_env(shell_data *datashell)
{
	int length;
	char *error;
	char *ver_str;
	char *msg;

	ver_str = aux_itoa(datashell->counter);
	msg = ": Unable to add/remove from environment\n";
	length = _strlen(datashell->argve[0]) + _strlen(ver_str);
	length += _strlen(datashell->args[0]) + _strlen(msg) + 4;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}

	_strcpy(error, datashell->argve[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datashell->args[0]);
	_strcat(error, msg);
	_strcat(error, "\0");
	free(ver_str);

	return (error);
}
/**
 * error_path_126 - error message for path and failure denied permission.
 * @datashell: data relevant (counter, arguments).
 *
 * Return: The error string.
 */
char *error_path_126(shell_data *datashell)
{
	int length;
	char *ver_str;
	char *error;

	ver_str = aux_itoa(datashell->counter);
	length = _strlen(datashell->argve[0]) + _strlen(ver_str);
	length += _strlen(datashell->args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, datashell->argve[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datashell->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}
