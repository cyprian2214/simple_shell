#include "Header.h"
size_t custom_strlen(const char *str);
/**
 * custom_signal_handler - Handle signals for Ctrl+C
 * @signal: The signal number
 * Return: Nothing
 */
void custom_signal_handler(int signal)
{
	char *prompt = "\n$ ";

	(void)signal;
	write(1, prompt, custom_strlen(prompt));
	fflush(stdout);
}
