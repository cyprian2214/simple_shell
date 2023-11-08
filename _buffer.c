#include "Header.h"

/**
 * custom_strlen - Calculate the length of a string
 * @str: The input string
 * Return: The length of the string
 */
size_t custom_strlen(const char *str);

/**
 * custom_getline - Custom getline function
 * @line: Line buffer
 * @len: Length of the buffer
 * @stream: Stream to read from
 * Return: Number of characters read or -1 if fail
 */
ssize_t custom_getline(char **line, size_t *len, FILE *stream)
{
	char *custom_getline;
	ssize_t read;

	if (*line == NULL || *len == 0)
	{
		*len = 1024;
		*line = malloc(*len);
		if (*line == NULL)
		{
			return (-1);
		}
	}

	custom_getline = fgets(*line, *len, stream);
	if (custom_getline != NULL)
	{
		read = custom_strlen(*line);

		if (read > 0 && (*line)[read - 1] == '\n')
		{
			(*line)[read - 1] = '\0';
			read--;
		}
		return (read);
	}
	else
	{
		return (-1);
	}
}
