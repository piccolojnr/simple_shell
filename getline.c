#include "shell.h"
/**
 * get_input - gets input from stdin
 * @lineptr: pointer to a buffer
 * @n: size of buffer
 * @stream: stdin
 * @info: struct of information
 *
 * Return: 0 on success, -1 on failure
 */
int get_input(char **lineptr, size_t *n, FILE *stream, t_info *info)
{
ssize_t read_result;
int arg_count;
read_result = _getline(lineptr, n, stream);
if (read_result == -1)
{
perror("getline");
return (FAILURE);
}
else if (read_result == 0)
{
free(*lineptr);
_putchar('\n');
return (-2);
}
arg_count = parse_string(*lineptr, ";\n", &(*info).argv);
if (arg_count == -1)
{
free(*lineptr);
return (FAILURE);
}
(*info).argc = arg_count;
free(*lineptr);
return (0);
}
/**
 * __getline - reads a line from stdin
 * @lineptr: pointer to a buffer
 * @n: size of buffer
 * @stream: stdin
 *
 * Return: number of bytes read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
char *buf, *new_buf;
ssize_t bytes_read, total_bytes_read, i;
size_t buf_size;
int read_result, mode = isatty(fileno(stream));
if (lineptr == NULL || n == NULL || stream == NULL)
return (-1);
bytes_read = 0, buf_size = *n;
buf = malloc(sizeof(char) * buf_size);
if (buf == NULL)
return (-1);
total_bytes_read = 0;
while (1)
{
bytes_read = read(fileno(stream), buf +
total_bytes_read, buf_size - total_bytes_read);
if (bytes_read <= 0)
break;
total_bytes_read += bytes_read;
for (i = 0; i < total_bytes_read; i++)
{
if (buf[i] == '\n' && mode)
{
buf[i] = '\0', *lineptr = buf, *n = buf_size;
return (total_bytes_read);
}
}
if ((size_t)total_bytes_read == buf_size)
{
buf_size *= 2, new_buf = realloc(buf, buf_size);
if (new_buf == NULL)
{
free(buf);
return (-1);
}
buf = new_buf;
}
}
if (bytes_read == -1)
{
free(buf);
return (-1);
}
buf[total_bytes_read] = '\0';
read_result = total_bytes_read;
*lineptr = buf;
*n = buf_size;
return (read_result);
}
