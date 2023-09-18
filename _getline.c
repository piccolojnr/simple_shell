#include "shell.h"
/**
 * _fgets - get input from user
 * @info: struct with variables
 * @buffer: buffer with commands
 * @characters: number of characters
 * @fd: file descriptor
 */
char **_fgets(info_t *info, char **buffer, size_t *characters, int fd)
{
    int bufsize;

    bufsize = _getline(buffer, characters, fd);

    if (bufsize == -1)
    {
        _printf("\n");
        exit_shell(info, EXIT_FAILURE);
        return (NULL);
    }
    return (buffer);
}
/**
 * _realloc - reallocate a buffer
 * @ptr: pointer to the buffer
 * @size: new size of the buffer
 *
 * Return: pointer to the buffer
 */
void *_realloc(void *ptr, unsigned int size)
{
    char *p, *copy;
    void *ret;
    int i;

    p = (char *)_malloc(size);
    copy = (char *)ptr;
    ret = NULL;

    if (!p)
    {
        ret = p;
        return (ret);
    }

    i = 0;
    while (copy[i])
    {
        p[i] = copy[i];
        i++;
    }
    p[i] = '\0';
    ret = (void *)p;
    free(ptr);
    return (ret);
}
/**
 * _realloc2 - reallocate a buffer
 * @ptr: pointer to the buffer
 * @new_size: new size of the buffer
 * @old_size: old size of the buffer
 *
 * Return: pointer to the buffer
 */
void *_realloc2(void *ptr, unsigned int old_size, unsigned int new_size)
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
/**
 * _malloc - ...
 * @size: ...
 * 
 * Return: ...
*/
void *_malloc(unsigned int size)
{
    char *ptr = malloc(size);
    void *_ptr = NULL;
    unsigned int i = 0;

    if (!ptr)
    {
        _printf("ERROR ALLOCATING MEMORY");
        exit(EXIT_FAILURE);
    }
    while (i < size)
    {
        ptr[i] = '\0';
        i++;
    }
    _ptr = (void *)ptr;
    return (_ptr);
}
/**
 * _getline - get line of string from file
 * @lnptr: variable to store string
 * @size: number of strings stored
 * @fd: file to read from
 *
 * Return: the lenghh of lnptr or -1 on failure
 */

int _getline(char **lnptr, size_t *size, int fd)
{
    char buffer[BUFFER_SIZE + 1];
    int r = BUFFER_SIZE, len = 0, mode = isatty(0);
    char *tmp;

    *lnptr = (char *)_malloc(4);
    **lnptr = '\0';
    while (r == BUFFER_SIZE)
    {
        if (*lnptr && len > 0)
            if ((*lnptr)[len - 1] == '\n' && mode)
                break;
        r = read(fd, buffer, BUFFER_SIZE);
        if (r < 0 && errno == EINTR)
        {
            **lnptr = '\n', *(*lnptr + 1) = '\n', len = 2;
            return (len);
        }
        if (r < 0)
            exit(-1);
        if (r == 0 && mode)
            return (-1);
        tmp = _realloc(*lnptr, len + r + 4);
        *size = len + r + 4, *lnptr = tmp;
        buffer[r] = '\0', _strcat(*lnptr, buffer), len += r;
        if (!mode)
            replace_str(lnptr, "\n", ";");
    }
    if (!mode)
    {
        tmp = _realloc(*lnptr, _strlen(*lnptr) + 3);
        *lnptr = tmp;
        (*lnptr)[len] = '\n', (*lnptr)[len + 1] = '\0';
    }
    return (len);
}