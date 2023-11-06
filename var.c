#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimiter
 * @new_info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int is_chain(new_info_t *new_info, char *buf, size_t *p)
{
    size_t j = *p;

    if (buf[j] == '|' && buf[j + 1] == '|')
    {
        buf[j] = 0;
        j++;
        new_info->cmd_buf_type = CMD_OR;
    }
    else if (buf[j] == '&' && buf[j + 1] == '&')
    {
        buf[j] = 0;
        j++;
        new_info->cmd_buf_type = CMD_AND;
    }
    else if (buf[j] == ';') /* found end of this command */
    {
        buf[j] = 0; /* replace semicolon with null */
        new_info->cmd_buf_type = CMD_CHAIN;
    }
    else
        return (0);
    *p = j;
    return (1);
}

/**
 * check_chain - checks we should continue chaining based on the last status
 * @new_info: the parameter struct
 * @buf: the char buffer
 * @p: address of the current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(new_info_t *new_info, char *buf, size_t *p, size_t i, size_t len)
{
    size_t j = *p;

    if (new_info->cmd_buf_type == CMD_AND)
    {
        if (new_info->status)
        {
            buf[i] = 0;
            j = len;
        }
    }
    if (new_info->cmd_buf_type == CMD_OR)
    {
        if (!new_info->status)
        {
            buf[i] = 0;
            j = len;
        }
    }

    *p = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @new_info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(new_info_t *new_info)
{
    int i;
    new_list_t *node;
    char *p;

    for (i = 0; i < 10; i++)
    {
        node = node_starts_with(new_info->alias, new_info->argv[0], '=');
        if (!node)
            return (0);
        free(new_info->argv[0]);
        p = _strchr(node->str, '=');
        if (!p)
            return (0);
        p = _strdup(p + 1);
        if (!p)
            return (0);
        new_info->argv[0] = p;
    }
    return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @new_info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(new_info_t *new_info)
{
    int i = 0;
    new_list_t *node;

    for (i = 0; new_info->argv[i]; i++)
    {
        if (new_info->argv[i][0] != '$' || !new_info->argv[i][1])
            continue;

        if (!_strcmp(new_info->argv[i], "$?"))
        {
            replace_string(&(new_info->argv[i]),
                _strdup(convert_number(new_info->status, 10, 0)));
            continue;
        }
        if (!_strcmp(new_info->argv[i], "$$"))
        {
            replace_string(&(new_info->argv[i]),
                _strdup(convert_number(getpid(), 10, 0)));
            continue;
        }
        node = node_starts_with(new_info->env, &new_info->argv[i][1], '=');
        if (node)
        {
            replace_string(&(new_info->argv[i]),
                _strdup(_strchr(node->str, '=') + 1));
            continue;
        }
        replace_string(&new_info->argv[i], _strdup(""));
    }
    return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
    free(*old);
    *old = new;
    return (1);
}
