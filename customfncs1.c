#include "shell.h"

/**
 * var_build - builds an environment variable from its name and value
 *
 * @var_name:variable name
 * @var_value:variable value
 *
 * Return: string containing the full environment variable
 */

char *var_build(char *var_name, char *var_value)
{
	char *new_var;
	size_t size;

	size = _strlen(var_name) + _strlen(var_value) + 2;

	new_var = malloc(sizeof(char) * size);

	if (new_var == NULL)
	{
		perror("Error: Insufficient memory\n");
		return (NULL);
	}

	memset(new_var, 0, size);

	new_var = _strcat(new_var, var_name);
	new_var = _strcat(new_var, "=");
	new_var = _strcat(new_var, var_value);

	return (new_var);
}
