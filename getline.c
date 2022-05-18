#include "shell.h"

/**
 * line_ptr - reassigns the lineptr variable for _getline
 *
 * @lineptr: buffer to store an input string
 * @n: size of lineptr
 * @buf: string to assign to lineptr
 * @size: size of buffer
 *
 * Return: void
 */

void line_ptr(char **lineptr, size_t *n, char *buf, size_t size)
{
	if (*lineptr == NULL)
	{
		if (size > 120)
			*n = size;
		else
			*n = 120;

		*lineptr = buf;
	}
	else if (*n < size)
	{
		if (size > 120)
			*n = size;
		else
			*n = 120;

		*lineptr = buf;
	}
	else
	{
		_strcpy(*lineptr, buf);

		free(buf);
	}
}

/**
 * _getline - reads input from a stream
 *
 * @lineptr: buffer to store the input
 * @n: size of lineptr
 * @stream: stream to read from
 *
 * Return: the number of bytes read
 */

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t ret;
	char c = 'x', *buf;
	int r;

	if (input == 0)
		fflush(stream);
	else
		return (-1);

	input = 0;
	buf = malloc(sizeof(char) * 120);
	if (!buf)
		return (-1);
	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buf);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= 120)
			buf = _realloc(buf, input, input + 1);
		buf[input] = c;
		input++;
	}
	buf[input] = '\0';
	line_ptr(lineptr, n, buf, input);
	ret = input;
	if (r != 0)
		input = 0;

	return (ret);
}
