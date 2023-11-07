#include "Header.h"

/**
 * custom_strcat - concatenates two strings
 * @dest: destination string to append to
 * @src: source string to add
 *
 * Return: a pointer to the resulting string
 */
char *custom_strcat(char *dest, char *src)
{
	int i = 0;
	int j = 0;

	while (dest[i] != '\0')
		i++;

	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';

	return dest;
}
