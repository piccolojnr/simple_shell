#include "shell.h"
/**
 * run_shell_non_interactive - Runs the shell
 * @env_list: ...
 * @name: name of program
 *
 * Return: 0 for success, 1 for failure
 */
int run_shell_non_interactive(t_env **env_list, alias_t **alias_list, char *name)
{
    int i;
    char *line, **args;
    info_t *info = malloc(sizeof(info_t));
    size_t char_len = 0;
    FILE *file = NULL;

(void)alias_list;
(void)env_list;
    file = fopen(name, "r");
    if (file == NULL)
    {
        perror("failed to open file");
        free(info);
        return (EXIT_FAILURE);
    }

    while (_fgets(info, &line, &char_len, file) != NULL)
    {
        split_str(line, &args, "\n");
        if (args != NULL)
        {
            for (i = 0; args[i] != NULL; i++)
            {
                run_shell(&info, env_list, alias_list, args[i]);
            }
            free_args(args);
        }
    }

    free(line);
    free(info);
    fclose(file);
    return (EXIT_SUCCESS);
}
/**
 * run_shell - ...
 * @env_list: ...
 * @info: ...
 * @alias_list: ...
 * @line: ...
 *
 * Return: ...
 */
int run_shell(info_t **info, t_env **env_list, alias_t **alias_list, char *line)
{
    int i;
    char *filtered_line, **args, *trimmed, *delim = ";";

    if (is_line_empty(line))
        return (1);
    filtered_line = filter_comments(line);
    if (filtered_line == NULL)
        return (1);
    free(line);
    split_str(filtered_line, &args, delim);
    if (args == NULL)
        return (1);
    for (i = 0; args[i] != NULL; i++)
    {
        trimmed = trimWhitespace(args[i]);

        free(args[i]);
        args[i] = trimmed;

        if (args[i] != NULL && !is_line_empty(args[i]))
        {

            handle_logical_operators(args[i], info, env_list, alias_list);
        }
    }

    return (0);
}