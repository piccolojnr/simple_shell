#include "shell.h"
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 */
int _putchar(char c)
{
    return (write(1, &c, 1));
}
/**
 * _puts - prints a string
 * @s: string to print
 */
void _puts(char *s)
{
    int i = 0;
    while (s[i] != '\0')
    {
        _putchar(s[i]);
        i++;
    }
}
/**
 * _printf - prints formatted output
 * @format: format
 * @...: arguments
 *
 * Return: number of characters printed
 */
int _printf(const char *format, ...)
{
    char *s;
    int i, c;

    va_list args;
    va_start(args, format);

    for (i = 0; format[i] != '\0'; i++)
    {
        if (format[i] == '%')
        {
            i++; /* Move past the '%' character */

            /* Check for format specifiers */
            if (format[i] == 's')
            {
                s = va_arg(args, char *);
                _puts(s);
            }
            else if (format[i] == 'c')
            {
                c = va_arg(args, int);
                _putchar(c);
            }
            else
            {
                _putchar('%'); /* Print '%' if the format is unknown */
                if (format[i] != '\0')
                    _putchar(format[i]);
            }
        }
        else
        {
            _putchar(format[i]);
        }
    }

    va_end(args);
    return (1);
}
