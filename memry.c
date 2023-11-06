#include "shell.h"

/**
 * bfree - frees a pointer and NULLs the address
 * @new_info: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **new_info)
{
	if (new_info && *new_info)
	{
		free(*new_info);
		*new_info = NULL;
		return (1);
	}
	return (0);
}
