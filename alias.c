#include "shell.h"
/**
 * print_aliases - prints all aliases
 * @alias_list: aliases
 */
void print_aliases(alias_t *alias_list)
{
    alias_t *current = alias_list;

    while (current != NULL)
    {
        _printf("%s='%s'\n", current->name, current->value);
        current = current->next;
    }
}
/**
 * print_specific_alias - prints specific alias
 * @alias_list: aliases
 * @name: alias
 */
void print_specific_alias(alias_t *alias_list, char *name)
{
    alias_t *current;

    current = alias_list;
    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            _printf("%s='%s'\n", current->name, current->value);
            break;
        }
        current = current->next;
    }
}
/**
 * get_alias - gets alias
 * @alias_list: aliases
 * @name: name
 *
 * Return: alias
 */
alias_t *get_alias(alias_t *alias_list, char *name)
{
    alias_t *curr = alias_list;

    while (curr != NULL)
    {
        if (strcmp(curr->name, name) == 0)
            return (curr);
        curr = curr->next;
    }
    return (NULL);
}
/**
 * define_alias - defines alias
 * @info: info
 * @i: i
 * @alias_list: alias
 *
 * Return: 1 on success, 0 on failure
 */
int define_alias(info_t *info, int i, alias_t **alias_list)
{
    char *name, *value;

    name = _strtok(info->argv[i], "=");
    value = _strtok(NULL, "=");

    if (name != NULL && value != NULL)
    {
        /* Check if the alias already exists and update it */
        if (get_alias(*alias_list, name) != NULL)
        {
            if (!edit_alias_node(name, value, alias_list))
                return (0);
        }
        else
        {
            if (!add_alias_node_end(name, value, alias_list))
                return (0);
        }
    }
    else
        return (0);

    return (1);
}
