#include "main.h"

/**
 * add_var - adds a variable at the end
 * of a var list.
 * @head: head of the linked list.
 * @lvar: length of the variable.
 * @valu: valuue of the variable.
 * @lvalu: length of the valuue.
 * Return: address of the head.
 */
var *add_var(var **head, int lvar, char *valu, int lvalu)
{
	var *new, *temp;

	new = malloc(sizeof(var));
	if (new == NULL)
		return (NULL);

	new->var_len = lvar;
	new->valu = valu;
	new->val_lenu = lvalu;

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
 * free_var - frees a var list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_var(var **head)
{
	var *temp;
	var *curr;

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
