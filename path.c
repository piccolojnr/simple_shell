#include "shell.h"

/**
 * find_executable - Finds an executable in the PATH
 * @info: A pointer to a info_t struct
 *
 * Return: The exit status of the process
 */
int find_executable(t_info *info)
{
    int i, path_len;
    char *path;
    char **path_buffer = NULL;
    char *path_with_cmd;

    if (is_path(info->cmds[0]))
    {
        info->path = _strdup(info->cmds[0]);
        return (SUCCESS);
    }
    path = getenv("PATH");
    if (path == NULL || info->cmds[0] == NULL || path[0] == '\0')
        return (FAILURE);
    path_len = parse_string(path, ":", &path_buffer);
    if (path_len == -1)
        return (FAILURE);
    for (i = 0; i < path_len; i++)
    {

        path_with_cmd = concat_path_and_cmd(path_buffer[i], info->cmds[0]);
        if (path_with_cmd == NULL)
        {
            free(path_with_cmd);
            return (FAILURE);
        }
        if (access(path_with_cmd, X_OK) == 0)
        {
            ffree(path_buffer); /* Clean up the path_buffer */
            info->path = path_with_cmd;
            return (SUCCESS);
        }
        free(path_with_cmd);
    }

    ffree(path_buffer);
    return (FAILURE);
}
