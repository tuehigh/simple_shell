#include "our_own_shell.h"

/**
 * hsh - function for the main in shell loop
 * @param_info: Struct for parameter & return information
 * @args: Argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *param_info, char **args)
{
	ssize_t retst = 0;
	int builtin_result = 0;

	while (retst != -1 && builtin_result != -2)
	{
		clear_info(param_info);
		if (interactive(param_info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		retst = get_input(param_info);
		if (retst != -1)
		{
			set_info(param_info, args);
			builtin_result = find_builtin(param_info);
			if (builtin_result == -1)
				find_cmd(param_info);
		}
		else if (interactive(param_info))
			_putchar('\n');
		free_info(param_info, 0);
	}
	write_history(param_info);
	free_info(param_info, 1);
	if (!interactive(param_info) && param_info->status)
		exit(param_info->status);
	if (builtin_result == -2)
	{
		if (param_info->err_num == -1)
			exit(param_info->status);
		exit(param_info->err_num);
	}
	return (builtin_result);
}

/**
 * find_builtin - function that finds a builtin command
 * @param_info: Struct for parameter & return information
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int find_builtin(info_t *param_info)
{
	int i, builtin_result = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(param_info->argv[0], builtintbl[i].type) == 0)
		{
			param_info->line_count++;
			builtin_result = builtintbl[i].func(param_info);
			break;
	}
	return (builtin_result);
}

/**
 * find_cmd -function that finds a command in PATH
 * @param_info: Struct for parameter & return information
 *
 * Return: void
 */
void find_cmd(info_t *param_info)
{
	char *command_path = NULL;
	int i, arg_count;

	param_info->path = param_info->argv[0];
	if (param_info->linecount_flag == 1)
	{
		param_info->line_count++;
		param_info->linecount_flag = 0;
	}
	for (i = 0, arg_count = 0; param_info->arg[i]; i++)
		if (!is_delim(param_info->arg[i], " \t\n"))
			arg_count++;
	if (!arg_count)
		return;

	command_path = find_path(param_info, _getenv(param_info, "PATH="),
param_info->argv[0]);
	if (command_path)
	{
		param_info->path = command_path;
		fork_cmd(param_info);
	}
	else
	{
		if ((interactive(param_info) || _getenv(param_info, "PATH=")
|| param_info->argv[0][0] == '/') && is_cmd(param_info, param_info->argv[0]))
			fork_cmd(param_info);
		else if (*(param_info->arg) != '\n')
		{
			param_info->status = 127;
			print_error(param_info, "not found\n");
		}
	}
}

/**
 * fork_cmd - function to fork an exec thread to run a command
 * @param_info: Struct for parameter & return information
 *
 * Return: void
 */
void fork_cmd(info_t *param_info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(param_info->path, param_info->argv,
get_environ(param_info)) == -1)
		{
			free_info(param_info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(param_info->status));
		if (WIFEXITED(param_info->status))
		{
			param_info->status = WEXITSTATUS(param_info->status);
			if (param_info->status == 126)
				print_error(param_info, "Permission denied\n");
		}
	}
}

