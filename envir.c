#include "shell.h"

/**
 * _myenv - prints the current environment
 * @new_info: Structure containing potential arguments. Used to maintain
 *            a constant function prototype.
 * Return: Always 0
 */
int new_env(new_info_t *new_info)
{
    print_list_str(new_info->env);
    return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @new_info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *new_getenv(new_info_t *new_info, const char *name)
{
    new_list_t *node = new_info->env;
    char *p;

    while (node)
    {
        p = starts_with(node->str, name);
        if (p && *p)
            return (p);
        node = node->next;
    }
    return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @new_info: Structure containing potential arguments. Used to maintain
 *            a constant function prototype.
 * Return: Always 0
 */
int new_setenv(new_info_t *new_info)
{
    if (new_info->argc != 3)
    {
        _eputs("Incorrect number of arguements\n");
        return (1);
    }
    if (_setenv(new_info, new_info->argv[1], new_info->argv[2]))
        return (0);
    return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @new_info: Structure containing potential arguments. Used to maintain
 *            a constant function prototype.
 * Return: Always 0
 */
int new_unsetenv(new_info_t *new_info)
{
    int i;

    if (new_info->argc == 1)
    {
        _eputs("Too few arguements.\n");
        return (1);
    }
    for (i = 1; i <= new_info->argc; i++)
        _unsetenv(new_info, new_info->argv[i]);

    return (0);
}

/**
 * populate_env_list - populates env linked list
 * @new_info: Structure containing potential arguments. Used to maintain
 *                    a constant function prototype.
 * Return: Always 0
 */
int new_populate_env_list(new_info_t *new_info)
{
    new_list_t *node = NULL;
    size_t i;

    for (i = 0; new_info->environ[i]; i++)
        add_node_end(&node, new_info->environ[i], 0);
    new_info->env = node;
    return (0);
}
