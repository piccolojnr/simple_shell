#include "shell.h"
/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
/**
 * _strncmp  - compares two strangs.
 * @s1: the first strang
 * @s2: the second strang
 * @n: the number of bytes to compare
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strncmp(char *s1, char *s2, int n)
{
	int i = 0;

	while (*s1 && *s2 && i < n - 1)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
		i++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
/**
 * _strcat - Concatenate two strings.
 * @dest: Destination string where the result is stored.
 * @src: Source string to be concatenated to the destination.
 *
 * Return: A pointer to the destination string (`dest`).
 */
char *_strcat(char *dest, const char *src)
{
	char *result = dest;

	/* Move dest pointer to the end of the destination string */
	while (*dest)
		dest++;

	/* Copy characters from src to dest */
	while (*src)
		*dest++ = *src++;

	/* Null-terminate the result string */
	*dest = '\0';

	return (result);
}
/**
 * _strncat - Concatenate two strings.
 * @dest: Destination string where the result is stored.
 * @src: Source string to be concatenated to the destination.
 * @n: Number of bytes to be copied from src to dest.
 *
 * Return: A pointer to the destination string (`dest`).
 */
char *_strncat(char *dest, const char *src, int n)
{
	char *result = dest;
	int i = 0;

	/* Move dest pointer to the end of the destination string */
	while (*dest)
		dest++;

	/* Copy characters from src to dest */
	while (*src && i < n)
	{
		*dest++ = *src++;
		i++;
	}

	/* Null-terminate the result string */
	*dest = '\0';

	return (result);
}
/**
 * find_n_occ - finds the number of occurences of a substring
 * @str: the string to search
 * @sub: the substring to find
 *
 * Return: the number of occurences of the substring
 */
int find_n_occ(char *str, char *sub)
{
	char *tokenized = NULL, *new = NULL;
	int i = 0;

	if (_strlen(sub) > _strlen(str))
		return (0);

	new = _strdup(str);
	tokenized = _strtok(new, sub);
	while (tokenized != NULL)
	{
		i++;
		tokenized = _strtok(NULL, sub);
	}
	free(new);
	if (_strcmp(str + _strlen(str) - _strlen(sub), sub) == 0)
		i++;
	return (i - 1);
}
/**
 * replace_str - replaces a substring with another
 * @str: the string to search
 * @orig: the substring to find
 * @rep: the substring to replace
 *
 * Return: 0 on success and -1 on failure
 */
int replace_str(char **str, char *orig, char *rep)
{
	char *tokenized, *tmp, *new = _malloc(1);
	int _rep = 0, tor = find_n_occ(*str, orig), newlen = 0;

	if (tor == 0)
		return (0);

	tokenized = _strtok(*str, orig);
	*new = '\0';
	while (tokenized != NULL)
	{
		newlen = _strlen(new) + _strlen(tokenized) + _strlen(rep);
		tmp = _realloc(new, newlen + 2);
		_strcat(tmp, tokenized);
		if (_rep < tor)
			_strcat(tmp, rep);
		rep++, tokenized = _strtok(NULL, orig);
	}
	free(*str);
	*str = tmp;
	return (0);
}

/**
 * trimwhitespace - removes leading and trailing whitespace
 * @str: the string to trim
 *
 * Return: the trimmed string
 */
char *trimWhitespace(const char *str)
{
	size_t len, trimmedLen;
	char *trimmedStr;
	const char *end, *start;

	if (str == NULL)
	{
		return (NULL); /*Handle NULL input*/
	}

	/*Find the length of the input string*/
	len = _strlen((char *)str);

	/*Find the start of the trimmed string (skip leading whitespace)*/
	start = str;
	while (isspace((unsigned char)*start))
	{
		start++;
	}

	/*Find the end of the trimmed string (skip trailing whitespace)*/
	end = str + len - 1;
	while (end > start && isspace((unsigned char)*end))
	{
		end--;
	}

	/*Calculate the length of the trimmed string*/
	trimmedLen = end - start + 1;

	/*Allocate memory for the trimmed string and copy it*/
	trimmedStr = (char *)malloc(trimmedLen + 1); /*+1 for the null terminator*/
	if (trimmedStr == NULL)
	{
		return (NULL); /*Memory allocation failed*/
	}
	_strncpy(trimmedStr, start, trimmedLen);
	trimmedStr[trimmedLen] = '\0'; /*Null-terminate the trimmed string*/

	return (trimmedStr);
}
