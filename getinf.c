#include "shell.h"
#include "custom_functions.c"

/**
 * clear_info - initializes info_t struct
 * @new_info: struct address
 */
void clear_info(new_info_t *new_info)
{
    new_info->arg = NULL;
    new_info->argv = NULL;
    new_info->path = NULL;
    new_info->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @new_info: struct address
 * @av: argument vector
 */
void set_info(new_info_t *new_info, char **av)
{
    int i = 0;

    new_info->fname = av[0];
    if (new_info->arg)
    {
        new_info->argv = strtow(new_info->arg, " \t");
        if (!new_info->argv)
        {

            new_info->argv = malloc(sizeof(char *) * 2);
            if (new_info->argv)
            {
                new_info->argv[0] = _strdup(new_info->arg);
                new_info->argv[1] = NULL;
            }
        }
        for (i = 0; new_info->argv && new_info->argv[i]; i++)
            ;
        new_info->argc = i;

        replace_alias(new_info);
        replace_vars(new_info);
    }
}

/**
 * free_info - frees info_t struct fields
 * @new_info: struct address
 * @all: true if freeing all fields
 */
void free_info(new_info_t *new_info, int all)
{
    ffree(new_info->argv);
    new_info->argv = NULL;
    new_info->path = NULL;
    if (all)
    {
        if (!new_info->cmd_buf)
            free(new_info->arg);
        if (new_info->env)
            free_list(&(new_info->env));
        if (new_info->history)
            free_list(&(new_info->history));
        if (new_info->alias)
            free_list(&(new_info->alias));
        ffree(new_info->environ);
        new_info->environ = NULL;
        bfree((void **)new_info->cmd_buf);
        if (new_info->readfd > 2)
            close(new_info->readfd);
        _putchar(BUF_FLUSH);
    }
}
