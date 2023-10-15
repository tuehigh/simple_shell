#include "shell.h"

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

#include "shell.h"

/**
* _myhistory - function to displays the
*     history list, one command per line, preceded
* with line numbers, starting at 0.
* @info:pointer tonthe struct info
*
* Return: Always 0
*/
int _myhistory(info_t *info)
{
print_list(info->history);
return (0);
}

/**
* unset_alias -function to unsets an alias by removing it from the alias list
* @info: parameter struct
* @alias_str: the alias string
*
* Return: Always 0 on success, 1 on error
*/
int unset_alias(info_t *info, char *alias_str)
{
char *ptr, ch;
int ret;

ptr = _strchr(alias_str, '=');
if (!ptr)
return (1);
ch = *ptr;
*ptr = 0;
ret = delete_node_at_index(&(info->alias),
get_node_index(info->alias, node_starts_with(info->alias, alias_str, -1)));
*ptr = ch;
return (ret);
}

/**
* set_alias - function to sets an alias to a string
* @info: parameter struct
* @alias_str: the alias string
*
* Return: Always 0 on success, 1 on error
*/
int set_alias(info_t *info, char *alias_str)
{
char *ptr;

ptr = _strchr(alias_str, '=');
if (!ptr)
return (1);
if (!*++ptr)
return (unset_alias(info, alias_str));

unset_alias(info, alias_str);
return (add_node_end(&(info->alias), alias_str, 0) == NULL);
}

/**
* print_alias -function to prints an alias string
* @alias_node: the alias node
*
* Return: Always 0 on success, 1 on error
*/
int print_alias(list_t *alias_node)
{
char *ptr = NULL, *a = NULL;

if (alias_node)
{
ptr = _strchr(alias_node->str, '=');
for (a = alias_node->str; a <= ptr; a++)
_putchar(*a);
_putchar('\'');
_puts(ptr + 1);
_puts("'\n");
return (0);
}
return (1);
}

/**
* _myalias - function that act as the alias builtin (man alias)
* @info:pointer to the the struct info
*
* Return: Always 0
*/
int _myalias(info_t *info)
{
int index = 1;
char *p = NULL;
list_t *node = NULL;

if (info->argc == 1)
{
node = info->alias;
while (node)
{
print_alias(node);
node = node->next;
}
return (0);
}
while (info->argv[index])
{
p = _strchr(info->argv[index], '=');
if (p)
set_alias(info, info->argv[index]);
else
print_alias(node_starts_with(info->alias, info->argv[index], '='));
index++;
}

return (0);
}

