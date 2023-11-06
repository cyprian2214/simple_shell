#include "shell.h"

int is_cmd(new_info_t *new_info, char *path);
char *dup_chars(char *pathstr, int start, int stop);
char *find_path(new_info_t *new_info, char *pathstr, char *cmd);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char c);
int bfree(void **ptr);
char **strtow(char *str, char *d);
char **strtow2(char *str, char d);
