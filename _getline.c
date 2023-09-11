#include "shell.h"
/**
 * _getline - get a line from stdin
 * @lineptr: pointer to buffer
 * @n: size of the buffer
 * @stream: stream
 *
 * Return: number of bytes read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
    char *buf, c;
    ssize_t ret;
    static size_t char_length;
    int r;

    char_length = 0;
    if (lineptr == NULL || n == NULL || stream == NULL)
        return (-1);
    if (*n == 0)
        *n = BUFFER_SIZE;
    buf = malloc(sizeof(char) * BUFFER_SIZE);
    if (!buf)
        return (-1);
    while ((r = read(fileno(stream), &c, 1)) == 1 && c != '\n')
    {
        if (char_length >= *n)
        {
            *n *= 2;
            buf = _realloc(buf, *n / 2, *n);
            if (!buf)
            {
                free(buf);
                return (-1);
            }
        }
        buf[char_length++] = c;
    }
    if (r == -1 || (r == 0 && char_length == 0))
    {
        free(buf);
        return (-1);
    }
    buf[char_length] = '\0';
    if (*lineptr)
        free(*lineptr);
    *lineptr = buf;
    ret = char_length;
    return (ret);
}
/**
 * get_input - get input from user
 * @info: struct with variables
 */
void get_input(info_t *info)
{
    info->char_len = getline(&info->line, &info->line_len, stdin);
    if ((info->char_len == -1))
    {
        if (feof(stdin))
        {
            /* EOF reached, exit gracefully */
            free(info->line);
            free(info);
            exit_shell(info, EXIT_SUCCESS); /* or any other appropriate action */
        }
        else
        {
            /* Error reading input */
            perror("Error reading input");
            free(info->line);
            free(info);
            exit_shell(info, EXIT_FAILURE);
        }
    }
}
/**
 * _realloc - reallocate a buffer
 * @ptr: pointer to the buffer
 * @new_size: new size of the buffer
 * @old_size: old size of the buffer
 * 
 * Return: pointer to the buffer
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    void *mem;
    char *ptr_copy, *filler;
    unsigned int index;

    if (new_size == old_size)
        return (ptr);

    if (ptr == NULL)
    {
        mem = malloc(new_size);
        if (mem == NULL)
            return (NULL);
        return (mem);
    }

    if (new_size == 0 && ptr != NULL)
    {
        return (NULL);
    }

    ptr_copy = ptr;
    mem = malloc(sizeof(*ptr_copy) * new_size);
    if (mem == NULL)
    {
        return (NULL);
    }

    filler = mem;

    for (index = 0; index < old_size && index < new_size; index++)
        filler[index] = *ptr_copy++;

    return (mem);
}
