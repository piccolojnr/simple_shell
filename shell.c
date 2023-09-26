#include "shell.h"
/**
 * run_interactive_shell - run interactive mode
 * @info: ...
 */
void run_interactive_shell(t_info *info)
{
    char *line;
    size_t buf_size = BUFFER_SIZE;
    int input_res;

    (void)buf_size;
    while (1)
    {
        _puts("$ ");
        input_res = get_input(&line, &buf_size, stdin, info);
        if (input_res == FAILURE)
            continue;
        else if (input_res == EXIT)
            return;
        if (start_process(info) == EXIT)
        {
            ffree(info->argv);
            return;
        }
        ffree(info->argv);
    }
}
/**
 * run_non_interactive_shell - run non-interactive shell
 * @info: ...
 */
void run_non_interactive_shell(t_info *info)
{
    char *line;
    size_t buf_size = BUFFER_SIZE;
    int input_res;
    (void)buf_size;
    input_res = get_input(&line, &buf_size, stdin, info);
    if (input_res == FAILURE || input_res == EXIT)
        return;
    if (start_process(info) == EXIT)
    {
        ffree(info->argv);
        return;
    }
    ffree(info->argv);
}
/**
 * run_file - run file
 * @info: ...
 */
void run_file(t_info *info)
{
    char *line;
    size_t buf_size = BUFFER_SIZE;
    FILE *fp;
    int input_res;
    (void)buf_size;
    fp = fopen(info->filename, "r");
    if (fp == NULL)
    {
        perror(info->filename);
        return;
    }

    while (1)
    {
        input_res = get_input(&line, &buf_size, fp, info);
        if (input_res == FAILURE || input_res == EXIT || feof(fp))
            break;
        if (start_process(info) == EXIT)
        {
            ffree(info->argv);
            fclose(fp);
            return;
        }
        ffree(info->argv);
    }
    fclose(fp);
}
/**
 * start_process - processes info
 * @info: ...
 *
 * Return: ...
 */
int start_process(t_info *info)
{
    int i, cmds_count, fork_status;
    for (i = 0; info->argv[i]; i++)
    {
        cmds_count = parse_string(info->argv[i], " \t", &(*info).cmds);
        if (cmds_count == -1)
        {
            continue;
        }
        else if (cmds_count == 0)
        {
            ffree(info->cmds);
            continue;
        }
        else
        {
            info->cmds_len = cmds_count;
            fork_status = fork_command(info);
            ffree(info->cmds);
            if (fork_status == EXIT)
                return (-2);
        }
    }
    return (SUCCESS);
}
/**
 * fork_command - ...
 * @info: ...
 *
 * Return: ...
 */
int fork_command(t_info *info)
{
    pid_t child_pid;
    /* Fork and execute external commands */
    child_pid = fork();
    if (child_pid == -1)
    {
        perror(info->cmds[0]);
        return (FAILURE);
    }
    if (child_pid == 0)
    {
        /* child process */
        if (info->path == NULL)
            info->path = info->cmds[0];
        if (execve(info->path, info->cmds, info->env) == -1)
        {
            perror(info->cmds[0]);
            return (FAILURE);
        }
        return (EXIT_SUCCESS);
    }
    else
    {
        /* Parent process */
        if (wait(&info->status) == -1)
        {
            perror(info->cmds[0]);
            return (FAILURE);
        }
        return (WEXITSTATUS(info->status));
    }
}
