#include "shell.h"

/**
* _myenv -function to Print the current environment variables.
* @info: Structure containing potential arguments and environment information.
*        Used to maintain a consistent function prototype.
* Return: Always 0 (indicating success).
*/
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
* _getenv -function that Get the value of a specific environment variable.
* @info: Structure containing potential arguments and environment information.
*        Used to maintain a consistent function prototype.
* @name: The name of the environment variable to retrieve.
*
* Return: The value of the specified environment variable or NULL if not found.
*/
char *_getenv(info_t *info, const char *name)
{
	list_t *current_env = info->env;
	char *env_value;

	while (current_env)
	{
		env_value = starts_with(current_env->str, name);
		if (env_value && *env_value)
			return (env_value);
		current_env = current_env->next;
	}
	return (NULL);
}

/**
* _mysetenv -function Set or modify an environment variable.
* @info: Structure containing potential arguments and environment information.
*        Used to maintain a consistent function prototype.
* Return: 0 on success,
* return 1 if the operation fails (e.g., incorrect number of arguments).
*/
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
* _myunsetenv - function that Remove an environment variable.
* @info: Structure containing potential arguments and environment information.
*        Used to maintain a consistent function prototype.
* Return: Always 0 (indicating success).
*/
int _myunsetenv(info_t *info)
{
	int i = 1;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	while (i <= info->argc)
	{
		_unsetenv(info, info->argv[i]);
		i++;
	}
	return (0);
}

/**
* populate_env_list -function to  Populate an environment linked list
*	with system environment variables.
* @info: Structure containing potential arguments and environment information.
*        Used to maintain a consistent function prototype.
* Return: Always 0 (indicating success).
*/
int populate_env_list(info_t *info)
{
	list_t *env_list = NULL;
	size_t i = 0;

	while (environ[i])
	{
		add_node_end(&env_list, environ[i], 0);
		i++;
	}
	info->env = env_list;
	return (0);
}

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
ourInformation->env_changed = delete_node_at_index(&(ourInformation->env), u);
u = 0;
the_node = ourInformation->env;
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

