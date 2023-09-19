#include "shell.h"
/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 * @env_list: ...
 * @alias_list: ...
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info_t *info, t_env **env_list, alias_t **alias_list)
{
int i, built_in_ret = -1;
builtin_table builtintbl[] = {
{"which", which_builtin},
{"exit", exit_builtin},
{"env", env_builtin},
{"setenv", setenv_builtin},
{"unsetenv", unsetenv_builtin},
{"cd", chdir_builtin},
{"alias", alias_builtin},
{NULL, NULL}};
/* find built-in command */
for (i = 0; builtintbl[i].type; i++)
{
if (info->argv[0] && _strcmp(info->argv[0], builtintbl[i].type) == 0)
{
built_in_ret = builtintbl[i].func(info, env_list, alias_list);
break;
}
}
return (built_in_ret);
}
/**
 * replace_env_var - Replaces environment variable references in argv
 * @info: Pointer to the info_t structure
 * @env_list: Pointer to the linked list of environment variables
 */
void replace_env_var(info_t **info, t_env *env_list)
{
pid_t shell_pid = getpid();
int i;
char *env_name;
for (i = 0; i < (*info)->argc; i++)
{
if ((*info)->argv[i][0] == '$' && (*info)->argv[i][1] != '\0'
&& (*info)->argv[i][1] != '\n')
{
env_name = (*info)->argv[i] + 1; /* Skip the '$' symbol */
if (_strcmp(env_name, "$") == 0)
replace_with_pid(info, i, shell_pid);
else if (_strcmp(env_name, "?") == 0)
replace_with_status(info, i);
else
replace_with_env_var(info, i, env_name, env_list);
}
}
replace_args(info);
}
/**
 * replace_with_pid - ...
 * @info: ...
 * @index: ...
 * @shell_pid: ...
*/
void replace_with_pid(info_t **info, int index, pid_t shell_pid)
{
char *new_arg = int_to_string((int)shell_pid);

if (new_arg == NULL)
{
perror("int_to_string");
exit_shell(*info, EXIT_FAILURE);
}
free((*info)->argv[index]);
(*info)->argv[index] = new_arg;
}
/**
 * replace_with_status - ...
 * @info: ...
 * @index: ...
*/
void replace_with_status(info_t **info, int index)
{
char *new_arg = int_to_string((*info)->status);

if (new_arg == NULL)
{
perror("int_to_string");
exit_shell(*info, EXIT_FAILURE);
}
free((*info)->argv[index]);
(*info)->argv[index] = new_arg;
}
/**
 * replace_with_env_var - ...
 * @info: ...
 * @index: ...
 * @env_name: ...
 * @env_list: ...
*/
void replace_with_env_var(info_t **info, int index, const char *env_name,
							t_env *env_list)
{
char *env_value = _getenv(env_name, env_list);
if (env_value)
{
char *new_arg = _strdup(env_value);
if (!new_arg)
{
perror("strdup");
exit_shell(*info, EXIT_FAILURE); /* Handle memory allocation failure */
}
free((*info)->argv[index]); /* Free the old argument */
(*info)->argv[index] = new_arg; /* Assign the new argument */
}
else
{
/* Environment variable not found, set the argument to NULL */
free((*info)->argv[index]); /* Free the old argument */
(*info)->argv[index] = NULL;
}
}
