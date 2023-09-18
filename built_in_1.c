#include "shell.h"

/**
 * chdir_builtin - Change the current working directory.
 * @info: Pointer to the info_t struct containing command info.
 * @env_list: Pointer to the environment variable linked list (not used here).
 *
 * Return: 0 on success, 1 on failure.
 */
int chdir_builtin(info_t *info, t_env **env_list, alias_t **alias_list)
{
    char *oldpwd, *newpwd, *pwd;

    (void)alias_list;

    /* Check the number of arguments */
    if (info->argc != 2)
    {
        _printf("Usage: cd <directory>\n");
        return (1); /* Return an error code */
    }

    if (strcmp((const char *)info->argv[1], "-") == 0)
    {
        oldpwd = _getenv("OLDPWD", *env_list);
        if (oldpwd)
        {
            free(info->argv[1]);
            info->argv[1] = oldpwd;
            return (chdir_builtin(info, env_list, alias_list));
        }
    }

    pwd = _strdup(info->argv[1]);

    /* Save the current working directory in the oldpwd variable */
    oldpwd = _getenv("PWD", *env_list);
    if (oldpwd)
    {
        if (_setenv("OLDPWD", oldpwd, 1, env_list) == 0)
        {
            perror("OLDPWD setting failed");
            return 1; /* Return an error code */
        }
    }

    /* Attempt to change the current directory */
    if (chdir(pwd) == -1)
    {
        free(pwd);
        perror("chdir");
        return 1; /* Return an error code */
    }

    /* Update the PWD environment variable */
    newpwd = getcwd(NULL, 0);
    if (newpwd)
    {
        if (_setenv("PWD", newpwd, 1, env_list) == 0)
        {
            perror("PWD setting failed");
            free(pwd);
            free(newpwd);
            return 1; /* Return an error code */
        }
        free(newpwd);
    }
    else
    {
        free(pwd);
        perror("getcwd");
        return 1; /* Return an error code */
    }

    free(pwd);
    return (0); /* Return success */
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