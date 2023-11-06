#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @new_info: Structure containing potential arguments. Used to maintain
 *           constant function prototype.
 *  Return: Always 0
 */
int _myhistory(new_info_t *new_info)
{
    print_list(new_info->history);
    return (0);
}

/**
 * unset_alias - sets alias to string
 * @new_info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(new_info_t *new_info, char *str)
{
    char *p, c;
    int ret;

    p = _strchr(str, '=');
    if (!p)
        return (1);
    c = *p;
    *p = 0;
    ret = delete_node_at_index(&(new_info->alias),
        get_node_index(new_info->alias, node_starts_with(new_info->alias, str, -1)));
    *p = c;
    return (ret);
}

/**
 * set_alias - sets alias to string
 * @new_info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(new_info_t *new_info, char *str)
{
    char *p;

    p = _strchr(str, '=');
    if (!p)
        return (1);
    if (!*++p)
        return (unset_alias(new_info, str));

    unset_alias(new_info, str);
    return (add_node_end(&(new_info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(new_list_t *node)
{
    char *p = NULL, *a = NULL;

    if (node)
    {
        p = _strchr(node->str, '=');
        for (a = node->str; a <= p; a++)
            _putchar(*a);
        _putchar('\'');
        _puts(p + 1);
        _puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @new_info: Structure containing potential arguments. Used to maintain
 *           constant function prototype.
 *  Return: Always 0
 */
int _myalias(new_info_t *new_info)
{
    int i = 0;
    char *p = NULL;
    new_list_t *node = NULL;

    if (new_info->argc == 1)
    {
        node = new_info->alias;
        while (node)
        {
            print_alias(node);
            node = node->next;
        }
        return (0);
    }
    for (i = 1; new_info->argv[i]; i++)
    {
        p = _strchr(new_info->argv[i], '=');
        if (p)
            set_alias(new_info, new_info->argv[i]);
        else
            print_alias(node_starts_with(new_info->alias, new_info->argv[i], '='));
    }

    return (0);
}
