#include "shell.h"
/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0
 */
int main(int argc, char **argv)
{
	info_t *info = _malloc(sizeof(info_t));
	char input[MAX__LENGTH];

	if (!create_env_list(&info))
	{
		perror("main");
		exit(EXIT_FAILURE);
	}

	if (argc == 1)
	{

		if (!isatty(fileno(stdin)))
			if (custom_fgets(input, sizeof(input), stdin) != NULL)
			{
				run_shell(&info, input);
			}
			else
			{
				perror("main");
				free(info);
			}
		else
			return (run_shell_interactive(&info));
	}
	else if (argc == 2)
		return (run_shell_non_interactive(&info, argv[1]));
	return (0);
}
