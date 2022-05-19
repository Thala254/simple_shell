#include "main.h"

/**
 * cd_shell - changes current directory
 *
 * @datashell: data relevant
 * Return: 1 on success
 */
int cd_shell(shell_data *datashell)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = datashell->args[1];

	if (dir != NULL)
	{
		ishome = _strcmp("$HOME", dir);
		ishome2 = _strcmp("~", dir);
		isddash = _strcmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_to_home(datashell);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_previous(datashell);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dot(datashell);
		return (1);
	}

	cd_to(datashell);

	return (1);
}
