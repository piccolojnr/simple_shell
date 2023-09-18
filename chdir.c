#include "shell.h"
/**
 * handle_dash - handles the - command
 * @info: Structure containing potential arguments. Used to maintain
 * @env_list: list of environment variables
 * 
 * Return: 0 on success, 1 on failure
*/
int handle_dash(info_t *info, t_env **env_list)
{
    char *oldpwd = _getenv("OLDPWD", *env_list);

    if (oldpwd)
    {
        free(info->argv[1]);
        info->argv[1] = oldpwd;
        return (change_directory(info->argv[1], env_list));
    }
    else
    {
        _printf("OLDPWD not set.\n");
        return (1);
    }
}
/**
 * change_directory - changes directory
 * @target_directory: target directory
 * @env_list: list of environment variables
 * 
 * Return: 0 on success, 1 on failure
*/
int change_directory(const char *target_directory, t_env **env_list)
{
    char *pwd = _strdup(target_directory);
    char *oldpwd = _getenv("PWD", *env_list);
    char *newpwd;

    if (oldpwd)
    {
        if (_setenv("OLDPWD", oldpwd, 1, env_list) == 0)
        {
            perror("OLDPWD setting failed");
            return (1); /* Return an error code */
        }
    }

    if (chdir(pwd) == -1)
    {
        free(pwd);
        perror("chdir");
        return (1); /* Return an error code */
    }

    newpwd = getcwd(NULL, 0);

    if (newpwd)
    {
        if (_setenv("PWD", newpwd, 1, env_list) == 0)
        {
            perror("PWD");
            free(pwd);
            free(newpwd);
            return (1); /* Return an error code */
        }
        free(newpwd);
    }
    else
    {
        free(pwd);
        perror("getcwd");
        return (1);
    }

    free(pwd);
    return (0); /* Return success */
}