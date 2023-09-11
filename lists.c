#include "shell.h"
/*
 * create_env_list - creates a linked list of environment variables
 *
 * Return: head of the linked list
 */
t_env *create_env_list()
{
	int i;
	t_env *head = NULL;
	char *name, *value, **args;

	for (i = 0; environ[i]; i++)
	{
		args = split_env(environ[i]);
		if (!args)
			continue;

		name = args[0];
		value = args[1];

		add_node_end(&head, name, value);
	}

	return (head);
}
/**
 * add_node_end - adds a new node at the beginning
 * @head: head of the linked list
 * @str: string to store in the list
 *
 * Return: address of the head
 */
t_env *add_node_end(t_env **head, const char *name, const char *value)
{
	t_env *new = (t_env *)malloc(sizeof(t_env));

	if (new == NULL)
		return (NULL);

	new->name = _strdup(name);
	if (new->name == NULL)
	{
		free(new);
		return (NULL);
	}
	new->value = _strdup(value);
	if (new->value == NULL)
	{
		free(new);
		return (NULL);
	}

	new->next = *head;
	*head = new;

	return (new);
}
/**
 * remove_node - Removes a node with a specified name from a linked list
 * @head: pointer to the head of the linked list
 * @name: name of the node to remove
 *
 * Return: 1 on success, 0 on failure
 */
int remove_node(t_env **head, char *name)
{
	t_env *current = *head;
	t_env *prev = NULL;

	if (*head == NULL)
		return (0);

	while (current != NULL)
	{
		if (_strcmp(current->name, name) == 0)
		{
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;
			free(current->name);
			free(current->value);
			free(current);
		}
		prev = current;
		current = current->next;
	}

	return (0);
}
/**
 * edit_node - Finds and edits a node in a linked list
 * @head: Pointer to the head of the linked list
 * @name: Name of the node to edit
 * @new_value: New value to set for the node
 *
 * Return: 1 on success, 0 on failure (node not found or memory allocation error)
 */
int edit_node(t_env **head, char *name, char *new_value)
{
	t_env *current = *head;

	if (*head == NULL)
		return (0);

	while (current != NULL)
	{
		if (_strcmp(current->name, name) == 0)
		{
			free(current->value);

			current->value = _strdup(new_value);

			if (current->value == NULL)
				return (0);

			return (1);
		}
		current = current->next;
	}

	return (0);
}
/**
 * free_env_list - frees a linked list
 * @head: head of the linked list
 */
void free_env_list(t_env *head)
{
	t_env *current;

	while (head)
	{
		current = head;
		head = head->next;
		free(current->name);
		free(current->value);
	}
}