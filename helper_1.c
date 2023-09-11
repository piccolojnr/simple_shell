#include "shell.h"
/**
 * split_env - Splits environment variables into name and value.
 * @str: The string to split.
 *
 * Return: A pointer to an array of strings containing name and value.
 *         The first element is the name, and the second element is the value.
 *         Returns NULL on failure or if the input string is not in the format
 *         "name=value".
 */
char **split_env(char *str)
{
    char *str_copy, **result = NULL, *name = NULL,
                    *value = NULL, *token = NULL;
    const char *delimiter = "=";

    if (!str)
        return NULL;

    /* Make a copy of the input string to avoid modifying it */
    str_copy = _strdup(str);
    if (!str_copy)
    {
        perror("Memory allocation failed");
        return NULL;
    }

    /* Split the string using the delimiter */
    token = strtok(str_copy, delimiter);
    if (token)
    {
        name = _strdup(token);
        if (!name)
        {
            perror("Memory allocation failed");
            free(str_copy);
            return NULL;
        }

        token = strtok(NULL, delimiter);
        if (token)
        {
            value = _strdup(token);
            if (!value)
            {
                perror("Memory allocation failed");
                free(name);
                free(str_copy);
                return NULL;
            }
        }
    }

    /* Allocate memory for the result array */
    result = (char **)malloc(sizeof(char *) * 2);
    if (!result)
    {
        perror("Memory allocation failed");
        free(name);
        free(value);
        free(str_copy);
        return NULL;
    }

    /* Set the result array elements */
    result[0] = name;
    result[1] = value;

    /* Clean up and return the result */
    free(str_copy);
    return result;
}
