#include "shell.h"

/**
 * add_alias_node_end - adds a new node at the beginning
 * @name: name of the node
 * @value: value of the node
 * @alias_list: head of the linked list
 *
 * Return: 1 on success, 0 on failure
 */
int add_alias_node_end(const char *name, const char *value, alias_t **alias_list)
{
	alias_t *new = (alias_t *)malloc(sizeof(alias_t));

	if (new == NULL)
		return (0);

	new->name = _strdup(name);
	if (new->name == NULL)
	{
		perror("add alias node");
		free(new);
		return (0);
	}
	new->value = _strdup(value);

	new->next = *alias_list;
	*alias_list = new;

	return (1);
}
/**
 * remove_alias_node - Removes a node with a specified name from a linked list
 * @name: name of the node to remove
 * @alias_list: head of the linked list
 *
 * Return: 1 on success, 0 on failure
 */
int remove_alias_node(char *name, alias_t **alias_list)
{
	alias_t *current = *alias_list;
	alias_t *prev = NULL;

	if (alias_list == NULL)
		return (0);

	while (current != NULL)
	{
		if (_strcmp(current->name, (char *)name) == 0)
		{
			if (prev == NULL)
				*alias_list = current->next;
			else
				prev->next = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return (1);
		}
		prev = current;
		current = current->next;
	}

	return (0);
}
/**
 * edit_alias_node - Finds and edits a node in a linked list
 * @name: Name of the node to edit
 * @new_value: New value to set for the node
 * @alias_list: Head of the linked list
 *
 * Return: 1 on success, 0 on failure
 */
int edit_alias_node(char *name, char *new_value, alias_t **alias_list)
{
	alias_t *current = *alias_list;

	if (alias_list == NULL)
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
