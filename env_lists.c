#include "shell.h"
/**
 * create_env_list - creates a linked list of environment variables
 * @env_list: pointer to a pointer to the head of the list
 * @environ: pointer to the environment variables
 *
 * Return: 1 on success, 0 on failure
 */
int create_env_list(t_env **env_list, char **env)
{
	int i;
	t_env *head = NULL;
	char *name, *value, **args;

	if (env == NULL)
		return (0);

	if (env_list != NULL)
	{
		free_env_list(*env_list);
	}

	for (i = 0; env[i]; i++)
	{
		args = split_env(env[i]);
		if (!args)
			continue;

		name = args[0];
		value = args[1];

		if (!add_env_node_end(name, value, env_list))
		{
			free_env_list(head);
			return (0);
		}
	}

	return (1);
}
/**
 * add_env_node_end - adds a new node at the beginning
 * @name: name of the node
 * @value: value of the node
 * @env_list: pointer to a pointer to the head of the list
 *
 * Return: 1 on success, 0 on failure
 */
int add_env_node_end(const char *name, const char *value, t_env **env_list)
{
	t_env *new = (t_env *)malloc(sizeof(t_env));

	if (new == NULL)
		return (0);

	new->name = _strdup(name);
	if (new->name == NULL)
	{
		perror("add node 1");
		free(new);
		return (0);
	}
	new->value = _strdup(value);

	new->next = *env_list;
	*env_list = new;

	return (1);
}
/**
 * remove_env_node - Removes a node with a specified name from a linked list
 * @name: name of the node to remove
 * @env_list: pointer to a pointer to the head of the list
 *
 * Return: 1 on success, 0 on failure
 */
int remove_env_node(char *name, t_env **env_list)
{
	t_env *current = *env_list;
	t_env *prev = NULL;

	if (env_list == NULL)
		return (0);

	while (current != NULL)
	{
		if (_strcmp(current->name, (char *)name) == 0)
		{
			if (prev == NULL)
				*env_list = current->next;
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
 * edit_env_node - Finds and edits a node in a linked list
 * @name: Name of the node to edit
 * @new_value: New value to set for the node
 * @env_list: pointer to a pointer to the head of the list
 *
 * Return: 1 on success, 0 on failure
 */
int edit_env_node(char *name, char *new_value, t_env **env_list)
{
	t_env *current = *env_list;

	if (env_list == NULL)
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
