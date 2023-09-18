#include "shell.h"

/**
 * chdir_builtin - Change the current working directory.
 * @info: Pointer to the info_t struct containing command info.
 * @env_list: Pointer to the environment variable linked list (not used here).
 * @alias_list: Pointer to the alias linked list (not used here).
 *
 * Return: 0 on success, 1 on failure.
 */
int chdir_builtin(info_t *info, t_env **env_list, alias_t **alias_list)
{
    (void)alias_list;

    if (info->argc != 2)
    {
        _printf("Usage: cd <directory>\n");
        return 1; /* Return an error code */
    }

    char *target_directory = info->argv[1];

    if (strcmp(target_directory, "-") == 0)
    {
        return handleDash(info, env_list);
    }
    else
    {
        return changeDirectory(target_directory, env_list);
    }
}
/**
 * alias_builtin - Define or display aliases.
 * @info: Pointer to the info_t struct containing command info.
 * @env_list: Pointer to the environment variable linked list (not used here).
 * @alias_list: Pointer to the alias linked list.
 *
 * Return: 0 on success, 1 on failure.
 */
int alias_builtin(info_t *info, t_env **env_list, alias_t **alias_list)
{
    int i, num;

    (void)env_list;

    if (info->argc == 1)
    {
        print_aliases(*alias_list);
    }
    else if (info->argc > 1)
    {
        for (i = 1; i < info->argc; i++)
        {
            num = find_num_sub(info->argv[i], "=");

            if (num == 1)
                define_alias(info, i, alias_list);
            else if (num == 0)
                print_specific_alias(*alias_list, info->argv[i]);
            else
            {
                perror("alias");
                return (1);
            }
        }
    }

    return (0);
}