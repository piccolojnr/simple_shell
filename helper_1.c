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
/**
 * concat_path_and_cmd - Concatenates a path and command.
 * @path: The path to concatenate.
 * @cmd: The command to concatenate.
 *
 * Return: A pointer to the concatenated string.
 */
char *concat_path_and_cmd(const char *path, const char *cmd)
{
    /* Calculate the total length needed for the result */
    size_t path_len = _strlen(path);
    size_t cmd_len = _strlen(cmd);
    /* +1 for '/' and +1 for '\0' */
    size_t result_len = path_len + 1 + cmd_len + 1;

    /* Allocate memory for the result */
    char *result = (char *)malloc(result_len);
    if (result == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    /* Copy the path and add a '/' character */
    _strcpy(result, path);
    _strcat(result, "/");

    /* Concatenate the command */
    _strcat(result, cmd);

    return result;
}
