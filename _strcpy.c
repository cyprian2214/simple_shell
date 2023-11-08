#include "Header.h"

/**
 * custom_strcpy - Copy one string to another
 * @dest: The destination string
 * @src: The source string
 * Return: Pointer to the copied string
 */
char *custom_strcpy(char *dest, char *src)
{
	int len = 0, i = 0;

	len = 0;
	while (src[len] != '\0')
		len++;

	for (; i < len; i++)
		dest[i] = src[i];

	dest[i] = '\0';

	return (dest);
}
