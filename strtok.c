#include "shell.h"

/**
 * tok_len - locates the delimiter index marking the end
 * of the first token contained within a string
 *
 * @str: string to be searched
 * @delim: delimiter character
 *
 * Return: the delimiter index marking the end of the intitial token
 * that's pointed to
 */

int tok_len(char *str, char *delim)
{
	int i = 0, len = 0;

	while (*(str + index) && *(str + index) != *delim)
	{
		len++;
		i++;
	}

	return (len);
}

/**
 * tok_count - counts the number of delimited words contained in a string
 *
 * @str: string to be searched
 * @delim: delimiter character
 *
 * Return: the number of words contained within str
 */

int tok_count(char *str, char *delim)
{
	int i, tok = 0, len = 0;

	for (i = 0; *(str + i); i++)
		len++;

	for (i = 0; i < len; i++)
	{
		if (*(str + i) != *delim)
		{
			tok++;
			i += tok_len(str + i, delim);
		}
	}

	return (tok);
}

/**
 * _strtok - tokenizes a string
 *
 * @str: string to be tokenized
 * @delim: delimiter character
 *
 * Return: pointer to an array containing the tokenized words
 */

char **_strtok(char *str, char *delim)
{
	char **ptr;
	int i = 0, j, k, tok, letters;

	tokens = tok_count(str, delim);
	if (tok == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tok + 2));
	if (!ptr)
		return (NULL);

	for (k = 0; k < tok; k++)
	{
		while (str[i] == *delim)
			i++;
		letters = tok_len(str + i, delim);

		ptr[k] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[k])
		{
			for (i -= 1; i >= 0; i--)
				free(ptr[i]);

			free(ptr);
			return (NULL);
		}
		for (j = 0; j < letters; j++)
		{
			ptr[k][j] = str[i];
			i++;
		}
		ptr[k][j] = '\0';
	}
	ptr[k] = NULL;
	ptr[k + 1] = NULL;

	return (ptr);
}
