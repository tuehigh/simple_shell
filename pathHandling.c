#include "our_own_shell.h"

/**
* is_cmd -function to determines if a file is an executable command
* @info: the info struct
* @file_path: path to the file
*
* Return: 1 if true, 0 otherwise
*/
int is_cmd(info_t *info, char *file_path)
{
	struct stat file_stat;
	(void)info;

	if (!file_path || stat(file_path, &file_stat))
		return (0);
	if (S_ISREG(file_stat.st_mode))
	{
		return (1);
	}
	return (0);
}

/**
* dup_chars -function to duplicates characters
* @path_string: the PATH string
* @start: starting index
* @stop: stopping index
*
* Return: pointer to a new buffer
*/
char *dup_chars(char *path_string, int start, int stop)
{
	static char buffer[1024];
	int k = 0;
	int i = start;

	while (i < stop)
	{
		if (path_string[i] != ':')
		{
			buffer[k++] = path_string[i];
		}
		i++;
	}
	buffer[k] = 0;
	return (buffer);
}

/**
* find_path - function to finds this cmd in the PATH string
* @info: the info struct
* @path_string: the PATH string
* @cmd: the cmd to find
*
* Return: full path of cmd if found or NULL
*/
char *find_path(info_t *info, char *path_string, char *cmd)
{
	int i = 0;
	int curr_pos = 0;
	char *path;

	if (!path_string)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!path_string[i] || path_string[i] == ':')
		{
			path = dup_chars(path_string, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!path_string[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
