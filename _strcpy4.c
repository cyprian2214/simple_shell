#include "Header.h"

/**
 * custom_strcpy - copies the string pointed to by src
 * including the terminating null byte (\0)
 * to the buffer pointed to by dest
 * @dest: destination string
 * @src: source string to copy
 *
 * Return: a pointer to the destination string
 */
char *custom_strcpy(char *dest, const char *src)
{
	int len = 0;
	int i = 0;

	len = 0;
	while (src[len] != '\0')
		len++;

	for (; i < len; i++)
		dest[i] = src[i];

	dest[i] = '\0';

	return dest;
}
