#include "Header.h"

/**
 * custom_strlen - Calculate the length of a string
 * @str: The input string
 * Return: The length of the string
 */
size_t custom_strlen(const char *str)
{
	size_t i = 0;

	while (str[i] != '\0')
		i++;
	return (i);
}
