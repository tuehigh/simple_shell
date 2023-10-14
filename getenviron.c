#include "shell.h"

/**
* get_environ - returns string array duplicate of our environment
* @ourInformation: contains potential arguments. Used to maintain
*          constant function prototype.
* Return: Always 0
*/
char **get_environ(info_t *ourInformation)
{
if (!ourInformation->environ || ourInformation->env_changed)
{
ourInformation->environ = list_to_strings(ourInformation->env);
ourInformation->env_changed = 0;
}

return (ourInformation->environ);
}

/**
* _unsetenv - Remove an environment variable
* @ourInformation: Structure containing potential arguments. Used to maintain
*        constant function prototype.
*  Return: 1 on delete, 0 otherwise
* @theVariable: the string env var property
*/
int _unsetenv(info_t *ourInformation, char *theVariable)
{
list_t *the_node = ourInformation->env;
size_t u = 0;
char *o;

if (!the_node || !theVariable)
return (0);

while (the_node)
{
o = starts_with(the_node->str, theVariable);
if (o && *o == '=')
{
info->env_changed = delete_node_at_index(&(info->env), i);
i = 0;
node = ourInformation->env;
continue;
}
the_node = the_node->next;
u++;
}
return (ourInformation->env_changed);
}

/**
* _setenv - Initialize a new environment variable,
*             or modify an existing one
* @info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
* @var: the string env var property
* @value: the string env var value
*  Return: Always 0
*/
int _setenv(info_t *ourInformation, char *theVariable, char *our_value)
{
char *the_buff = NULL;
list_t *the_node;
char *o;

if (!theVariable || !our_value)
return (0);

the_buff = malloc(_strlen(theVariable) + _strlen(our_value) + 2);
if (!the_buff)
return (1);
_strcpy(the_buff, theVariable);
_strcat(the_buff, "=");
_strcat(the_buff, our_value);
the_node = ourInformation->env;
while (the_node)
{
o = starts_with(the_node->str, theVariable);
if (o && *o == '=')
{
free(the_node->str);
the_node->str = the_buff;
ourInformation->env_changed = 1;
return (0);
}
the_node = the_node->next;
}
add_node_end(&(ourInformation->env), the_buff, 0);
free(the_buff);
ourInformation->env_changed = 1;
return (0);
}
