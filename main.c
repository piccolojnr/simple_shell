#include "shell.h"
/**
 * main - Entry point
 * @argc: number of arguments
 * @argv: array of arguments
 * @env: environment variables
 *
 * Return: 0 on success
 */
int main(int argc, char **argv, char **env)
{
t_info info = INFO_INIT;

info.env = env;

if (argc == 2)
{
/* get commands from a file */
info.filename = argv[1];
run_file(&info);
}
else
{
if (is_interactive())
{
run_interactive_shell(&info);
}
else
{
run_non_interactive_shell(&info);
}
}
return (EXIT_SUCCESS);
}
