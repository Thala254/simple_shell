#include "main.h"

/**
 * check_env - checks if the typed variable is an env variable
 *
 * @h: head of linked list
 * @in: inp string
 * @data: data structure
 * Return: no return
 */
void check_env(var **h, char *in, shell_data *data)
{
	int row, chr, j, lvalu;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lvalu = _strlen(_envr[row] + chr + 1);
				add_var(h, j, _envr[row] + chr + 1, lvalu);
				return;
			}

			if (in[j] == _envr[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	add_var(h, j, NULL, 0);
}

/**
 * check_vars - check if the typed variable is $$ or $?
 *
 * @h: head of the linked list
 * @in: inp string
 * @st: last status of the Shell
 * @data: data structure
 * Return: no return
 */
int check_vars(var **h, char *in, char *st, shell_data *data)
{
	int i, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(data->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_var(h, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				add_var(h, 2, data->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				add_var(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				add_var(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_var(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_var(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_var(h, 0, NULL, 0);
			else
				check_env(h, in + i, data);
		}
	}

	return (i);
}

/**
 * replaced_inp - replaces string into variables
 *
 * @head: head of the linked list
 * @inp: inp string
 * @new_inp: new inp string (replaced)
 * @nlen: new length
 * Return: replaced string
 */
char *replaced_inp(var **head, char *inp, char *new_inp, int nlen)
{
	var *indx;
	int i, j, k;

	indx = *head;
	for (j = i = 0; i < nlen; i++)
	{
		if (inp[j] == '$')
		{
			if (!(indx->var_len) && !(indx->val_lenu))
			{
				new_inp[i] = inp[j];
				j++;
			}
			else if (indx->var_len && !(indx->val_lenu))
			{
				for (k = 0; k < indx->var_len; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->val_lenu; k++)
				{
					new_inp[i] = indx->valu[k];
					i++;
				}
				j += (indx->var_len);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			new_inp[i] = inp[j];
			j++;
		}
	}

	return (new_inp);
}

/**
 * rep_var - calls functions to replace string into vars
 *
 * @inp: inp string
 * @datashell: data structure
 * Return: replaced string
 */
char *rep_var(char *inp, shell_data *datashell)
{
	var *head, *indx;
	char *status, *new_inp;
	int olen, nlen;

	status = aux_itoa(datashell->status);
	head = NULL;

	olen = check_vars(&head, inp, status, datashell);

	if (head == NULL)
	{
		free(status);
		return (inp);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->val_lenu - indx->var_len);
		indx = indx->next;
	}

	nlen += olen;

	new_inp = malloc(sizeof(char) * (nlen + 1));
	new_inp[nlen] = '\0';

	new_inp = replaced_inp(&head, inp, new_inp, nlen);

	free(inp);
	free(status);
	free_var(&head);

	return (new_inp);
}
