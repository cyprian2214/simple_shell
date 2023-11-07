#include "Header.h"

/**
 * custom_strlen - custom string length function
 * @str: string to calculate length
 * Return: number of characters in the string
 */
size_t custom_strlen(const char *str);

/**
 * custom_getline - custom getline function
 * @line: line buffer
 * @len: length of buffer
 * @stream: stream to read from
 * Return: number of characters read or -1 if fail
 */
ssize_t custom_getline(char **line, size_t *len, FILE *stream)
{
	char *buffer;
	ssize_t bytes_read;

	if (*line == NULL || *len == 0)
	{
		*len = 1024;
		*line = malloc(*len);
		if (*line == NULL)
		{
			return (-1);
		}
	}

	buffer = fgets(*line, *len, stream);
	if (buffer != NULL)
	{
		bytes_read = custom_strlen(*line);

		if (bytes_read > 0 && (*line)[bytes_read - 1] == '\n')
		{
			(*line)[bytes_read - 1] = '\0';
			bytes_read--;
		}
		return (bytes_read);
	}
	else
	{
		return (-1);
	}
}
