#include "shell.h"

/**
 * isterminal - check if it's a terminal
 *
 * Return: void
 */

void isterminal(void)
{
	if (isatty(STDIN_FILENO))
		_puts("#cisfun$ ");
}

/**
 * signal_handler - checks if Ctrl C is pressed
 * @sig_num: int
 * Return: void
 */
void signal_handler(int sig_num)
{
	if (sig_num == SIGINT)
		_puts("\n#cisfun$ ");
}

/**
 * _EOF - handles the End of File
 * @len: getline function's return value
 * @buf: buffer
 * Return: void
 */

void _EOF(int len, char *buf)
{
	(void)buf;
	if (len == -1)
	{
		if (isatty(STDIN_FILENO))
		{
			_puts("\n");
			free(buf);
		}
		exit(0);
	}
}

/**
 * main - shell
 *
 * Return: 0 always
 */

int main(void)
{
	ssize_t len = 0;
	char *buf = NULL, **arv;
	size_t size = 0;

	signal(SIGINT, signal_handler);
	while (len != EOF)
	{
		isterminal();
		len = getline(&buf, &size, stdin);
		_EOF(len, buf);
		arv = splitstring(buf, " \n");
		if (!arv || !arv[0])
			execute(arv);
		else
		{
			
		}
	}

	return (0);
}
