#include "main.h"

/**
 * add_sep - adds a separator found at the end
 * of a list_sep.
 * @head: head of the linked list.
 * @sep: separator found (; | &).
 * Return: address of the head.
 */
list_sep *add_sep(list_sep **head, char sep)
{
	list_sep *new, *temp;

	new = malloc(sizeof(list_sep));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_list_sep - frees a list_sep
 * @head: head of the linked list.
 * Return: no return.
 */
void free_list_sep(list_sep **head)
{
	list_sep *temp;
	list_sep *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * add_line - adds a command line at the end
 * of a command_list.
 * @head: head of the linked list.
 * @line: command line.
 * Return: address of the head.
 */
command_list *add_line(command_list **head, char *line)
{
	command_list *new, *temp;

	new = malloc(sizeof(command_list));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_command_list - frees a command_list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_command_list(command_list **head)
{
	command_list *temp;
	command_list *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}
