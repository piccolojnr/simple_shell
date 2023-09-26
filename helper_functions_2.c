#include "shell.h"
/**
 * is_path - checks to see if str is a path
 * @str: ..
 *
 * Return: 1 for is path eelse 0
 */
int is_path(const char *str)
{
	if (str == NULL || str[0] == '\0')
	{
		return (0); /* Empty string is not a path */
	}

	/* Check for common path separators such as '/' and '\' */
	if (strchr(str, '/') != NULL || strchr(str, '\\') != NULL)
	{
		return (1); /* Contains a path separator, likely a path */
	}

	/* Check for Windows drive letter followed by ':' */
	if (str[1] == ':' && ((str[0] >= 'A' && str[0] <= 'Z')
	|| (str[0] >= 'a' && str[0] <= 'z')))
	{
		return (1); /* Matches the format of a Windows path */
	}

	return (0);
}