#include "shell.h"

/**
 * hsh - main shell loop
 * @new_info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(new_info_t *new_info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(new_info);
		if (interactive(new_info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(new_info);
		if (r != -1)
		{
			set_info(new_info, av);
			builtin_ret = find_builtin(new_info);
			if (builtin_ret == -1)
				find_cmd(new_info);
		}
		else if (interactive(new_info))
			_putchar('\n');
		free_info(new_info, 0);
	}
	write_history(new_info);
	free_info(new_info, 1);
	if (!interactive(new_info) && new_info->status)
		exit(new_info->status);
	if (builtin_ret == -2)
	{
		if (new_info->err_num == -1)
			exit(new_info->status);
		exit(new_info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @new_info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(new_info_t *new_info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(new_info->argv[0], builtintbl[i].type) == 0)
		{
			new_info->line_count++;
			built_in_ret = builtintbl[i].func(new_info);
			break;
	}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @new_info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(new_info_t *new_info)
{
	char *path = NULL;
	int i, k;

	new_info->path = new_info->argv[0];
	if (new_info->linecount_flag == 1)
	{
		new_info->line_count++;
		new_info->linecount_flag = 0;
	}
	for (i = 0, k = 0; new_info->arg[i]; i++)
		if (!is_delim(new_info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(new_info, _getenv(new_info, "PATH="), new_info->argv[0]);
	if (path)
	{
		new_info->path = path;
		fork_cmd(new_info);
	}
	else
	{
		if ((interactive(new_info) || _getenv(new_info, "PATH=")
			|| new_info->argv[0][0] == '/') && is_cmd(new_info, new_info->argv[0]))
			fork_cmd(new_info);
		else if (*(new_info->arg) != '\n')
		{
			new_info->status = 127;
			print_error(new_info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @new_info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(new_info_t *new_info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(new_info->path, new_info->argv, get_environ(new_info)) == -1)
		{
			free_info(new_info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(new_info->status));
		if (WIFEXITED(new_info->status))
		{
			new_info->status = WEXITSTATUS(new_info->status);
			if (new_info->status == 126)
				print_error(new_info, "Permission denied\n");
		}
	}
}
