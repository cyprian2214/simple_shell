#include "Header.h"

/**
 * custom_strcat - Concatenate two strings
 * @final_str: String to append to
 * @str_to: String to add
 *
 * Return: A pointer to the resulting string
 */
char *custom_strcat(char *final_str, char *str_to)
{
	int i, j;

	i = 0;
	while (final_str[i] != '\0')
		i++;

	j = 0;
	while (str_to[j] != '\0')
	{
		final_str[i] = str_to[j];
		j++;
		i++;
	}
	final_str[i] = '\0';

	return (final_str);
}
