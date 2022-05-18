#include "shell.h"

/**
 * line_part - partitions a line read from standard input and
 * inserts spaces to separate ";", "||", and "&&", and replaces "#" with '\0'
 *
 * @line: pointer to a line read from standard input
 * @len: length of line
 *
 * Return: void
 */

void line_part(char **line, ssize_t len)
{
	char *old_line, *new_line;
	char prev, current, next;
	size_t i, j;
	ssize_t new_len;

	new_len = get_new_len(*line);
	if (new_len == len - 1)
		return;
	new_line = malloc(new_len + 1);
	if (!new_line)
		return;
	j = 0;
	old_line = *line;
	for (i = 0; old_line[i]; i++)
	{
		current = old_line[i];
		next = old_line[i + 1];
		if (i != 0)
		{
			prev = old_line[i - 1];
			if (current == ';')
			{
				if (next == ';' && prev != ' ' && prev != ';')
				{
					new_line[j++] = ' ';
					new_line[j++] = ';';
					continue;
				}
				else if (prev == ';' && next != ' ')
				{
					new_line[j++] = ';';
					new_line[j++] = ' ';
					continue;
				}
				if (prev != ' ')
					new_line[j++] = ' ';
				new_line[j++] = ';';
				if (next != ' ')
					new_line[j++] = ' ';
				continue;
			}
			else if (current == '&')
			{
				if (next == '&' && prev != ' ')
					new_line[j++] = ' ';
				else if (prev == '&' && next != ' ')
				{
					new_line[j++] = '&';
					new_line[j++] = ' ';
					continue;
				}
			}
			else if (current == '|')
			{
				if (next == '|' && prev != ' ')
					new_line[j++]  = ' ';
				else if (prev == '|' && next != ' ')
				{
					new_line[j++] = '|';
					new_line[j++] = ' ';
					continue;
				}
			}
		}
		else if (current == ';')
		{
			if (i != 0 && old_line[i - 1] != ' ')
				new_line[j++] = ' ';
			new_line[j++] = ';';
			if (next != ' ' && next != ';')
				new_line[j++] = ' ';
			continue;
		}
		new_line[j++] = old_line[i];
	}
	new_line[j] = '\0';
	free(*line);
	*line = new_line;
}

/**
 * get_new_len - gets new length of line partitioned by ";", "||", "&&" or "#"
 *
 * @line: line being checked
 *
 * Return: new length of the line
 */

ssize_t get_new_len(char *line)
{
	size_t i;
	ssize_t new_len = 0;
	char current, next;

	for (i = 0; line[i]; i++)
	{
		current = line[i];
		next = line[i + 1];
		if (current == '#')
		{
			if (i == 0 || line[i - 1] == ' ')
			{
				line[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (current == ';')
			{
				if (next == ';' && line[i - 1] != ' ' && line[i - 1] != ';')
				{
					new_len += 2;
					continue;
				}
				else if (line[i - 1] == ';' && next != ' ')
				{
					new_len += 2;
					continue;
				}
				if (line[i - 1] != ' ')
					new_len++;
				if (next != ' ')
					new_len++;
			}
			else
				operator_check(&line[i], &new_len);
		}
		else if (current == ';')
		{
			if (i != 0 && line[i - 1] != ' ')
				new_len++;
			if (next != ' ' && next != ';')
				new_len++;
		}
		new_len++;
	}
	return (new_len);
}

/**
 * operator_check - checks a line for logical operators "||" or "&&"
 *
 * @line: pointer to the character to check in the line
 * @new_len: pointer to new length of the line
 *
 * Return: void
 */

void operator_check(char *line, ssize_t *new_len)
{
	char prev, current, next;

	prev = *(line - 1);
	current = *line;
	next = *(line + 1);

	if (current == '&')
	{
		if (next == '&' && prev != ' ')
			(*new_len)++;
		else if (prev == '&' && next != ' ')
			(*new_len)++;
	}
	else if (current == '|')
	{
		if (next == '|' && prev != ' ')
			(*new_len)++;
		else if (prev == '|' && next != ' ')
			(*new_len)++;
	}
}
