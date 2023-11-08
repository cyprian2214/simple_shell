#include "Header.h"
size_t custom_strlen(const char *str);
/**
 * custom_strdup - Duplicate a string
 * @str: The string to duplicate
 * Return: Pointer to the duplicated string
 */
char *custom_strdup(const char *str)
{
	size_t length = custom_strlen(str) + 1;
	char *new_str = (char *)malloc(length);
	size_t i = 0;

	if (new_str == NULL)
		return (NULL);

	for (; i < length; i++)
		new_str[i] = str[i];

	return (new_str);
}
