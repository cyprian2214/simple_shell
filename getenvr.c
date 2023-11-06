#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @new_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(new_info_t *new_info)
{
	if (!new_info->environ || new_info->env_changed)
	{
		new_info->environ = list_to_strings(new_info->env);
		new_info->env_changed = 0;
	}

	return (new_info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @new_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(new_info_t *new_info, char *var)
{
	new_list_t *node = new_info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			new_info->env_changed = delete_node_at_index(&(new_info->env), i);
			i = 0;
			node = new_info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (new_info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @new_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(new_info_t *new_info, char *var, char *value)
{
	char *buf = NULL;
	new_list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = new_info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			new_info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(new_info->env), buf, 0);
	free(buf);
	new_info->env_changed = 1;
	return (0);
}
