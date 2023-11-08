#include "Header.h"

/**
 * custom_strcmp - Compare two strings
 * @str1: The first string
 * @str2: The second string
 * Return: 0 if equal, positive/negative if different
 */
int custom_strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}

	return ((int)(*str1 - *str2));
}
