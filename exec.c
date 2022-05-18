#include "shell.h"

/**
 * splitstring - splits a string into array of pointers to words
 * @str: string
 * @delim: delimiter
 * Return: array of pointers to words
 */
char **splitstring(char *str, const char *delim)
{
	int i, wn;
	char **arr;
	char *token;
	char *copy;

	copy = malloc(_strlen(str) + 1);
	if (copy == NULL)
	{
		perror(_getenv("_"));
		return (NULL);
	}
	for (i = 0; str[i]; i++)
		copy[i] = str[i];
	copy[i] = '\0';
	token = strtok(copy, delim);
	arr = malloc(sizeof(char *) * 2);
	arr[0] = _strdup(token);

	i = 1;
	wn = 3;
	while (token)
	{
		token = strtok(NULL, delim);
		arr = _realloc(arr, (sizeof(char *) * (wn - 1)), (sizeof(char *) * wn));
		arr[i] = _strdup(token);
		i++;
		wn++;
	}
	free(copy);
	return (arr);
}

/**
 * execute - executes a command
 * @argv: array of arguments
 * Return: void
 */
void execute(char **argv)
{
	int pid, status;

	if (!argv || !argv[0])
		return;
	pid = fork();
	if (pid == -1)
		perror(_getenv("_"));
	if (pid == 0)
	{
		execve(argv[0], argv, environ);
			perror(argv[0]);
		exit(EXIT_FAILURE);
	}
	wait(&status);
}

/**
 * _realloc - reallocate memory dynamically
 * @ptr: pointer to be resized
 * @old_size: previous memory size
 * @new_size: new memory size
 * Return: rezized pointer
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new, *old;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	new = malloc(new_size);
	old = ptr;
	if (new == NULL)
		return (NULL);
	if (new_size > old_size)
	{
		for (i = 0; i < old_size; i++)
			new[i] = old[i];
		free(ptr);
		for (i = old_size; i < new_size; i++)
			new[i] = '\0';
	}
	if (new_size < old_size)
	{
		for (i = 0; i < new_size; i++)
			new[i] = old[i];
		free(ptr);
	}
	return (new);
}

/**
 * freearv - frees the array of pointers arv
 *@arv: array of pointers
 * Return: void
 */
void freearv(char **arv)
{
	int i;

	for (i = 0; arv[i]; i++)
		free(arv[i]);
	free(arv);
}
