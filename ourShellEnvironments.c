#include "our_own_shell.h"

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
