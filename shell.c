#include "Header.h"
#include <unistd.h>
/**
 * custom_getline - Read a line from input stream
 * @line: A pointer to the line buffer
 * @len: A pointer to the line length
 * @stream: The input stream
 * Return: Number of characters read
 */
ssize_t custom_getline(char **line, size_t *len, FILE *stream);

/**
 * main - Entry point for the custom shell
 * @ac: Argument count
 * @av: Argument vector
 * Return: Always 0
 */

int main(int ac, char **av)
{
	/* User prompt */
	char *prompt = "$ ";
	ssize_t chars_read = 0;
	ssize_t prompt_written = 0;
	char *line = NULL;
	size_t len = 0;
	size_t i = 0;
	size_t free_dir_i = 0;
	const char *delimiters = NULL;
	char *command_token = NULL;
	char **command = NULL;
	size_t max_command = 0;
	int child_pid = 0;
	int status = 0;
	char *path_env_var = NULL;
	int slash_i = 0;
	char *path = NULL;
	size_t max_directories = 0;
	char **directories = NULL;
	char *dir_token = NULL;
	size_t directories_i = 0;
	DIR *dir_stream = NULL;
	size_t searching_i = 0;
	struct dirent *entry = NULL;
	char *concat_path = NULL;
	int found = 0;
	char *err_msg = NULL;
	size_t size = 0;

	(void)ac;

	/* Handle signals */
	signal(SIGINT, custom_signal_handler);

	while (1)
	{
		line = NULL;
		delimiters = " \n\t\r\a";
		path = NULL;

		/* Display user prompt */
		if (isatty(STDIN_FILENO))
		{
			prompt_written = write(1, prompt, custom_strlen(prompt));
			if (prompt_written == -1)
			{
				perror("write");
				exit(1);
			}
		}

		fflush(stdout);

		/* Read user input */
		chars_read = custom_getline(&line, &len, stdin);

		if (chars_read == EOF)
		{
			break;
		}
		else if (chars_read == -1)
		{
			break;
		}

		/* Check for 'exit' command */
		if (custom_strcmp(line, "exit") == 0)
		{
			free(line);
			exit(0);
		}

		/* Check for 'env' command */
		if (custom_strcmp(line, "env") == 0)
		{
			int i = 0;

			for (; environ[i]; i++)
			{
				write(1, environ[i], custom_strlen(environ[i]));
				write(1, "\n", 1);
			}
			free(line);
			continue;
		}

		/* Tokenize the command */
		command_token = strtok(line, delimiters);

		if (command_token == NULL)
		{
			free(line);
			continue;
		}

		/* Allocate memory for the command array */
		max_command = 10;
		command = malloc(sizeof(char *) * max_command);
		i = 0;
		while (command_token != NULL)
		{
			if (i >= max_command)
			{
				max_command *= 2;
				command = realloc(command, sizeof(char *) * max_command);
				if (command == NULL)
				{
					perror("./hsh");
				}
			}

			/* Copy tokens into the command array */
			command[i] = custom_strdup(command_token);
			if (command[i] == NULL)
				continue;
			command_token = strtok(NULL, delimiters);
			i++;
		}
		/* Set the last element of the command array to NULL */
		command[i] = NULL;

		/* Check if the program name is a path or just a file name */
		slash_i = 0;
		while (line[slash_i] != '\0')
		{
			if (line[slash_i] == '/')
			{
				path = line;
				break;
			}
			slash_i++;
		}

		/* If the program name is not a path */
		if (path == NULL)
		{
			char *PATH = getenv("PATH");

			if (PATH == NULL)
				continue;

			path_env_var = custom_strdup(PATH);
			if (path_env_var == NULL)
				continue;

			dir_token = strtok(path_env_var, ":");
			if (dir_token == NULL)
			{
				perror("av[0]"); /* PROGRAM NAME ./hsh */
			}

			/* Allocate memory for the directories array */
			max_directories = 100;
			directories = malloc(sizeof(char *) * max_directories);
			directories_i = 0;

			while (dir_token != NULL)
			{
				if (directories_i >= max_directories)
				{
					max_directories *= 2;
					directories = realloc(directories, sizeof(char *) * max_directories);
					if (directories == NULL)
					{
						perror("realloc");
					}
				}
				/* Copy directory tokens into the directories array */
				directories[directories_i] = custom_strdup(dir_token);
				if (PATH == NULL)
					continue;
				dir_token = strtok(NULL, ":");
				directories_i++;
			}
			/* Null-terminate the directories array */
			directories[directories_i] = NULL;

			/* Search through directories to find the program */
			searching_i = 0;
			while (directories[searching_i] != NULL)
			{
				dir_stream = opendir(directories[searching_i]);

				if (dir_stream == NULL)
				{
					searching_i++;
					continue;
				}

				found = 0;
				entry = readdir(dir_stream);
				while (entry != NULL)
				{
					if (custom_strcmp(command[0], entry->d_name) == 0)
					{
						found = 1;
						break;
					}

					entry = readdir(dir_stream);
				}

				closedir(dir_stream);

				if (found == 1)
					break;

				searching_i++;
				if (searching_i == directories_i)
				{
					perror(command[0]);
				}
			}
		}

		/* Fork a new process for program execution */
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
		}
		else if (child_pid == 0)
		{
			if (path == NULL)
			{
				size = custom_strlen(directories[searching_i]) + custom_strlen(line) + 2;
				concat_path = malloc(size);
				if (concat_path == NULL)
				{
					perror("malloc");
				}

				/* Form the path to be executed */
				custom_strcpy(concat_path, directories[searching_i]);
				custom_strcat(concat_path, "/");
				custom_strcat(concat_path, command[0]);

				/* Execute the program */
				command[0] = concat_path;
				execve(command[0], command, environ);

				/* Handle execve failure */
				perror("execve");
				free(concat_path);
				free(command);
			}
			else
			{
				(void)av;
				(void)err_msg;
				execve(command[0], command, environ);
				perror("execve");
			}
		}

		/* Continue in the parent process */
		wait(&status);

		if (path == NULL)
		{
			for (free_dir_i = 0; directories[free_dir_i] != NULL; free_dir_i++)
			{
				free(directories[free_dir_i]);
			}
		}

		for (i = 0; command[i] != NULL; i++)
		{
			free(command[i]);
		}

		free(directories);
		free(path_env_var);
		free(concat_path);
		free(command);
		free(line);
	}
	free(line);
	if (isatty(STDIN_FILENO) == 1)
		write(1, "\n", 1);
	return (0);
}
