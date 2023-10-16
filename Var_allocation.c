#include "our_own_shell.h"

/**
* is_chain -function to test if the current
*   character in buffer is a chain delimiter
* @info: the parameter struct
* @buf: the character buffer
* @position: address of the current position in buf
*
* Return: 1 if a chain delimiter, 0 otherwise
*/
int is_chain(info_t *info, char *buf, size_t *position)
{
size_t j = *position;

if (buf[j] == '|' && buf[j + 1] == '|')
{
buf[j] = 0;
j++;
info->cmd_buf_type = CMD_OR;
}
else if (buf[j] == '&' && buf[j + 1] == '&')
{
buf[j] = 0;
j++;
info->cmd_buf_type = CMD_AND;
}
else if (buf[j] == ';') /* found the end of this command */
{
buf[j] = 0; /* replace semicolon with null */
info->cmd_buf_type = CMD_CHAIN;
}
else
{
return (0);
}
*position = j;
return (1);
}

/**
* check_chain - function to checks if we
*      should continue chaining based on the last status
* @info: the parameter struct
* @buf: the character buffer
* @position: address of the current position in buf
* @start_position: starting position in buf
* @length: length of buf
*
* Return: Void
*/
void check_chain(info_t *info, char *buf,
size_t *position, size_t start_position, size_t length)
{
size_t j = *position;

while (info->cmd_buf_type == CMD_AND)
{
if (info->status)
{
buf[start_position] = 0;
j = length;
}
}
while (info->cmd_buf_type == CMD_OR)
{
if (!info->status)
{
buf[start_position] = 0;
j = length;
}
}

*position = j;
}

/**
* replace_alias -function replaces aliases in the tokenized string
* @info: the parameter struct
*
* Return: 1 if replaced, 0 otherwise
*/
int replace_alias(info_t *info)
{
int count;
list_t *node;
char *ptr;

for (count = 0; count < 10; count++)
{
node = node_starts_with(info->alias, info->argv[0], '=');
if (!node)
{
return (0);
}
free(info->argv[0]);
ptr = _strchr(node->str, '=');
if (!ptr)
{
return (0);
}
ptr = _strdup(ptr + 1);
if (!ptr)
{
return (0);
}
info->argv[0] = ptr;
}
return (1);
}

/**
* replace_vars -function to replaces variables in the tokenized string
* @info: the parameter struct
*
* Return: 1 if replaced, 0 otherwise
*/
int replace_vars(info_t *info)
{
int i = 0;
list_t *node;

while (info->argv[i])
{
if (info->argv[i][0] != '$' || !info->argv[i][1])
{
i++;
continue;
}

if (!_strcmp(info->argv[i], "$?"))
{
replace_string(&(info->argv[i]), _strdup(convert_number(info->status, 10, 0)));
i++;
continue;
}
if (!_strcmp(info->argv[i], "$$"))
{
replace_string(&(info->argv[i]), _strdup(convert_number(getpid(), 10, 0)));
i++;
continue;
}
node = node_starts_with(info->env, &info->argv[i][1], '=');
if (node)
{
replace_string(&(info->argv[i]), _strdup(_strchr(node->str, '=') + 1));
i++;
continue;
}
replace_string(&info->argv[i], _strdup(""));
i++;
}
return (0);
}

/**
* replace_string - function to replaces a string
* @old_string: address of the old string
* @new_string: new string
*
* Return: 1 if replaced, 0 otherwise
*/
int replace_string(char **old_string, char *new_string)
{
free(*old_string);
*old_string = new_string;
return (1);
}
