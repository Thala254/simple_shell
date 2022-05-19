#include "main.h"

/**
 * get_error - calls the error according the builtin, syntax or permission
 * @datashell: data structure that contains arguments
 * @evalu: error valuue
 * Return: error
 */
int get_error(shell_data *datashell, int evalu)
{
	char *error;

	switch (evalu)
	{
	case -1:
		error = error_env(datashell);
		break;
	case 126:
		error = error_path_126(datashell);
		break;
	case 127:
		error = error_not_found(datashell);
		break;
	case 2:
		if (_strcmp("exit", datashell->args[0]) == 0)
			error = error_exit_shell(datashell);
		else if (_strcmp("cd", datashell->args[0]) == 0)
			error = error_get_cd(datashell);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	datashell->status = evalu;
	return (evalu);
}
