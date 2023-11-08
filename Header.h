#ifndef SHELL_H
#define SHELL_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <dirent.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

/**
 * custom_strcmp - Compare two strings
 * @str1: The first string
 * @str2: The second string
 * Return: 0 if equal, positive/negative if different
 */
int custom_strcmp(const char *str1, const char *str2);

/**
 * custom_signal_handler - Handle signals
 * @signal: The signal to handle
 */
void custom_signal_handler(int signal);

/**
 * custom_strlen - Calculate the length of a string
 * @str: The input string
 * Return: The length of the string
 */
size_t custom_strlen(const char *str);

/**
 * custom_strdup - Duplicate a string
 * @str: The string to duplicate
 * Return: Pointer to the duplicated string
 */
char *custom_strdup(const char *str);

/**
 * custom_strcat - Concatenate two strings
 * @dest: The destination string
 * @src: The source string
 * Return: Pointer to the concatenated string
 */
char *custom_strcat(char *dest, char *src);

/**
 * custom_strcpy - Copy one string to another
 * @dest: The destination string
 * @src: The source string
 * Return: Pointer to the copied string
 */
char *custom_strcpy(char *dest, char *src);

/* global variables */
extern char **environ;
#endif
