#include "shell.h"
/**
 * _getenv - gets the environment variable
 * @name: name of the environment variable
 * @env_list: ...
 *
 * Return: value of the environment variable
 */
char *_getenv(const char *name, t_env *env_list)
{
	t_env *current = env_list;

	if (name == NULL || name[0] == '\0' || _strchr((char *)name, '=') != NULL)
		return (NULL);

	while (current != NULL)
	{
		if (_strcmp(current->name, (char *)name) == 0)
		{
			return (current->value);
		}

		current = current->next;
	}

	return (NULL);
}
/**
 * _setenv - sets an environment variable
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @overwrite: overwrite the variable or not
 *
 * Return: 1 on success, 0 on failure
 */
int _setenv(const char *name, const char *value, int overwrite, t_env **env_list)
{
	/* Input validation */
	if (name == NULL || name[0] == '\0' || strchr((char *)name, '=') != NULL)
	{
		/* Invalid name, return failure */
		return (0);
	}

	/* TODO: Implement the logic to set the environment variable */
	if (overwrite)
	{
		if (edit_env_node((char *)name, (char *)value, env_list))
			return (1);
		else if (add_env_node_end((char *)name, (char *)value, env_list))
			return (1);
		else
			return (0);
	}
	else
	{
		if (add_env_node_end((char *)name, (char *)value, env_list))
			return (1);
		else
			return (0);
	}
}
/**
 * _unsetenv - deletes an environment variable
 * @name: name of the environment variable
 *
 * Return: 1 on success, 0 on failure
 */
int _unsetenv(const char *name, t_env **env_list)
{
	if (name == NULL || name[0] == '\0' || _strchr((char *)name, '=') != NULL)
		return (0);

	if (remove_env_node((char *)name, env_list))
		return (1);
	else
		return (0);
}
