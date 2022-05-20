#include "main.h"

/**
 * copy_info - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @valuue: valuue (env or alias)
 *
 * Return: new env or alias.
 */
char *copy_info(char *name, char *valuue)
{
	char *new;
	int len_name, val_lenuue, len;

	len_name = _strlen(name);
	val_lenuue = _strlen(valuue);
	len = len_name + val_lenuue + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, valuue);
	_strcat(new, "\0");

	return (new);
}

/**
 * set_env - sets an environment variable
 *
 * @name: name of the environment variable
 * @valuue: valuue of the environment variable
 * @datashell: data structure (environ)
 * Return: no return
 */
void set_env(char *name, char *valuue, shell_data *datashell)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; datashell->_environ[i]; i++)
	{
		var_env = _strdup(datashell->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(datashell->_environ[i]);
			datashell->_environ[i] = copy_info(name_env, valuue);
			free(var_env);
			return;
		}
		free(var_env);
	}

	datashell->_environ = _reallocdp(datashell->_environ, i,
					 sizeof(char *) * (i + 2));
	datashell->_environ[i] = copy_info(name, valuue);
	datashell->_environ[i + 1] = NULL;
}

/**
 * _setenv - compares env variables names
 * with the name passed.
 * @datashell: data relevant (env name and env valuue)
 *
 * Return: 1 on success.
 */
int _setenv(shell_data *datashell)
{

	if (datashell->args[1] == NULL || datashell->args[2] == NULL)
	{
		get_error(datashell, -1);
		return (1);
	}

	set_env(datashell->args[1], datashell->args[2], datashell);

	return (1);
}

/**
 * _unsetenv - deletes a environment variable
 *
 * @datashell: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv(shell_data *datashell)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (datashell->args[1] == NULL)
	{
		get_error(datashell, -1);
		return (1);
	}
	k = -1;
	for (i = 0; datashell->_environ[i]; i++)
	{
		var_env = _strdup(datashell->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, datashell->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		get_error(datashell, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; datashell->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = datashell->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(datashell->_environ[k]);
	free(datashell->_environ);
	datashell->_environ = realloc_environ;
	return (1);
}
