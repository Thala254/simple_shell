#include "main.h"

/**
 * read_line - reads the inp string.
 *
 * @i_eof: return valuue of getline function
 * Return: inp string
 */
char *read_line(int *i_eof)
{
	char *inp = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&inp, &bufsize, stdin);

	return (inp);
}
