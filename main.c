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
	info_t info = INFO_INIT;
	char input[MAX__LENGTH], **args = NULL, *trimm;
	int len, i, ret = 0;

	if (1)
	{
		if (argc == 1)
		{
			if (!isatty(fileno(stdin)))
				if (custom_fgets(input, sizeof(input), stdin) != NULL)
				{
					trimm = trimWhitespace(input);
					len = split_str(trimm, &args, "\n");
					free(trimm);
					if (args == NULL)
					{
						free_env(info.env);
						return (EXIT_FAILURE);
					}
					for (i = 0; i < len; i++)
						ret = run_shell(&info, args[i]);
					free_args(args);
				}
				else
					ret = EXIT_FAILURE;
			else
				ret = run_shell_interactive(&info);
		}
		else if (argc == 2)
			ret = run_shell_non_interactive(&info, argv[1]);
		else
			ret = EXIT_FAILURE;
	}
	else
		ret = EXIT_FAILURE;
	free_info(&info);
	return (ret);
}
/**
 * free_info - ...
 * @info: ...
 */
void free_info(info_t *info)
{
	free(info->argv);
	free_alias(info->aliases);
	free_env(info->env);
}
