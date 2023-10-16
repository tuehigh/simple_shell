#include "our_own_shell.h"

/**
* _myexit -function to exits the shell
* @inf: pointr to the struct info
* constant function prototype.
* Return: exits with a given exit status
* (0) if inf->argv[0] != "exit"
*/
int _myexit(info_t *inf)
{
int exit_check;

if (inf->argv[1])
{
exit_check = _erratoi(inf->argv[1]);
if (exit_check == -1)
{
inf->status = 2;
print_error(inf, "Illegal number: ");
_eputs(inf->argv[1]);
_eputchar('\n');
return (1);
}
inf->err_num = _erratoi(inf->argv[1]);
return (-2);
}
inf->err_num = -1;
return (-2);
}

/**
* _mycd - function that changes the current directory of the process
* @inf: Structure containing potential arguments. Used to maintain
* constant function prototype.
* Return: Always 0
*/
int _mycd(info_t *inf)
{
char *s, *dir, buffer[1024];
int chdir_ret;

s = getcwd(buffer, 1024);
if (!s)
_puts("TODO: >>getcwd failure emsg here<<\n");
if (!inf->argv[1])
{
dir = _getenv(inf, "HOME=");
if (!dir)
chdir_ret = chdir((dir = _getenv(inf, "PWD=")) ? dir : "/");
else
chdir_ret = chdir(dir);
}
else if (_strcmp(inf->argv[1], "-") == 0)
{
if (!_getenv(inf, "OLDPWD="))
{
_puts(s);
_putchar('\n');
return (1);
}
_puts(_getenv(inf, "OLDPWD=")), _putchar('\n');
chdir_ret = chdir((dir = _getenv(inf, "OLDPWD=")) ? dir : "/");
}
else
chdir_ret = chdir(inf->argv[1]);
if (chdir_ret == -1)
{
print_error(inf, "can't cd to ");
_eputs(inf->argv[1]), _eputchar('\n');
}
else
{
_setenv(inf, "OLDPWD", _getenv(inf, "PWD="));
_setenv(inf, "PWD", getcwd(buffer, 1024));
}
return (0);
}

/**
* _myhelp - function to changes the current directory of the process
* @inf: pointr to the struct info
* Return: Always 0
*/
int _myhelp(info_t *inf)
{
char **arg_array;

arg_array = inf->argv;
_puts("help call works. Function not yet implemented \n");
if (0)
_puts(*arg_array);
return (0);
}
