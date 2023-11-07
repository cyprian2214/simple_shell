#include "Header.h"

size_t custom_strlen(const char *str);

/**
 * custom_signal_handler - handles signals for Ctrl+C
 * @signal: signal number
 *
 * This function handles signals, specifically for Ctrl+C (SIGINT).
 */
void custom_signal_handler(int signal)
{
    char *prompt = "\n$ ";

    (void)signal;
    write(1, prompt, custom_strlen(prompt));
    fflush(stdout);
}
