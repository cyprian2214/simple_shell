#include "Header.h"

/**
 * custom_strcmp - compares two strings
 * @str1: first string to compare
 * @str2: second string to compare
 *
 * Return: 0 if the strings are equal, an integer indicating their difference
 */
int custom_strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}

	return (int)(*str1 - *str2);
}
