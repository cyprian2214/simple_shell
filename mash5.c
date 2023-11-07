#include "Header.h"

/**
 * custom_strdup - duplicate a string
 * @str: string to be duplicated
 *
 * Return: a pointer to the duplicated string
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

    return new_str;
}
