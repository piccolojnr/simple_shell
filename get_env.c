#include "shell.h"
/**
 * _getenv - gets the environment variable
 * @name: name of the environment variable
 *
 * Return: value of the environment variable
 */
char *_getenv(const char *name)
{
	int i;
	char *var;

	if (name == NULL || name[0] == '\0' || _strchr((char *)name, '=') != NULL)
		return (NULL);
	/* Iterate through the environment variables */
	for (i = 0; environ[i] != NULL; i++)
	{
		var = environ[i];
		if (strncmp(var, (char *)name, strlen((char *)name))
			== 0 && var[strlen((char *)name)] == '=')
			return (var + strlen((char *)name) + 1);
	}
	return (NULL);
}
/**
 * _setenv - sets an environment variable
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @overwrite: overwrite the variable or not
 *
 * Return: 0 on success, -1 on failure
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	int i, j, count = 0;
	size_t len;
	char *new_var, **new_environ;

	if (name == NULL || name[0] == '\0' || strchr((char *)name, '=') != NULL)
		return (-1);
	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], (char *)name, _strlen((char *)name))
			== 0 && environ[i][_strlen((char *)name)] == '=')
		{
			if (overwrite)
			{
				free(environ[i]);
				break;
			}
			else
				return (0);
		}
	}
	len = _strlen((char *)name) + _strlen((char *)value) + 2;
	new_var = malloc(len);
	if (new_var == NULL)
		return (-1);
	new_var = _strcpy(new_var, (char *)name);
	new_var = _strcat(new_var, "=");
	new_var = _strcat(new_var, (char *)value);
	for (j = 0; environ[j] != NULL; j++)
		;
	new_environ = malloc(sizeof(char *) * (count + 2));
	if (new_environ == NULL)
	{
		free(new_var);
		return (-1);
	}
	environ = new_environ;
	environ[count] = new_var;
	environ[count + 1] = NULL;
	return (0);
}
/**
 * _unsetenv - deletes an environment variable
 * @name: name of the environment variable
 *
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(const char *name)
{
	int i, j;

	if (name == NULL || name[0] == '\0' || _strchr((char *)name, '=') != NULL)
		/* Invalid variable (char *)name */
		return (-1);

	/* Find the variable to delete */
	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], (char *)name, strlen((char *)name))
			== 0 && environ[i][strlen((char *)name)] == '=')
		{
			/* Variable found, delete it */
			free(environ[i]);

			/* Shift the remaining variables to fill the gap */
			for (j = i; environ[j] != NULL; j++)
				environ[j] = environ[j + 1];

			return (0); /* Variable deleted successfully */
		}
	}

	return (0); /* Variable not found (no error) */
}
