#include "shell.h"

/**
 * _myexit - exits the shell
 * @new_info: Structure containing potential arguments. Used to maintain
 *           constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if new_info->argv[0] != "exit"
 */
int _myexit(new_info_t *new_info)
{
    int exit_status;

    if (new_info->argv[1]) {
        exit_status = _erratoi(new_info->argv[1]);
        if (exit_status == -1) {
            print_error(new_info, "Illegal number: ");
            _eputs(new_info->argv[1]);
            _eputchar('\n');
        } else {
            new_info->err_num = exit_status;
            return -1;
        }
    } else {
        new_info->err_num = 0;
        return -1;
    }
    return 0;
}

/**
 * _mycd - changes the current directory of the process
 * @new_info: Structure containing potential arguments. Used to maintain
 *           constant function prototype.
 *  Return: Always 0
 */
int _mycd(new_info_t *new_info)
{
    char *dir, buffer[1024];
    int chdir_ret;

    if (!new_info->argv[1]) {
        dir = _getenv(new_info, "HOME=");
        if (!dir)
            dir = _getenv(new_info, "PWD=");
    } else if (_strcmp(new_info->argv[1], "-") == 0) {
        dir = _getenv(new_info, "OLDPWD=");
        if (!dir) {
            dir = _getenv(new_info, "PWD=");
            _puts(dir);
            _putchar('\n');
            return 1;
        }
    } else {
        dir = new_info->argv[1];
    }

    chdir_ret = chdir(dir);
    if (chdir_ret == -1) {
        print_error(new_info, "can't cd to ");
        _eputs(dir);
        _eputchar('\n');
    } else {
        _setenv(new_info, "OLDPWD", _getenv(new_info, "PWD="));
        _setenv(new_info, "PWD", getcwd(buffer, 1024));
    }

    return 0;
}

/**
 * _myhelp - changes the current directory of the process
 * @new_info: Structure containing potential arguments. Used to maintain
 *           constant function prototype.
 *  Return: Always 0
 */
int _myhelp(new_info_t *new_info)
{
    char **arg_array;

    arg_array = new_info->argv;
    _puts("help call works. Function not yet implemented \n");
    if (0)
        _puts(*arg_array); /* temp att_unused workaround */
    return (0);
}
