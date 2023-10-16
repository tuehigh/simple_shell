#include "our_own_shell.h"

/**
* get_history_file - function to gets the history file
* @info: pointer to the struct parameter struct
*
* Return: return allocated string containg history file
*/

char *get_history_file(info_t *info)
{
char *buffer, *direc;

direc = _getenv(info, "HOME=");
if (!direc)
return (NULL);
buffer = malloc(sizeof(char) * (_strlen(direc) + _strlen(HIST_FILE) + 2));
if (!buffer)
return (NULL);
buffer[0] = 0;
_strcpy(buffer, direc);
_strcat(buffer, "/");
_strcat(buffer, HIST_FILE);
return (buffer);
}

/**
* write_history - function to creates a file, or appends to an existing file
* @info:pointer to the struct parameter
*
* Return: 1 on success, else -1
*/
int write_history(info_t *info)
{
ssize_t file_descriptor;
char *filename = get_history_file(info);
list_t *node = NULL;

if (!filename)
return (-1);

file_descriptor = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (file_descriptor == -1)
return (-1);
for (node = info->history; node; node = node->next)
{
_putsfd(node->str, file_descriptor);
_putfd('\n', file_descriptor);
}
_putfd(BUF_FLUSH, file_descriptor);
close(file_descriptor);
return (1);
}

/**
* read_history - reads history from file
* @info: the parameter struct
*
* Return: histcount on success, 0 otherwise
*/
int read_history(info_t *info)
{
int i, last_line = 0, line_count = 0;
ssize_t fd, read_len, file_size = 0;
struct stat st;
char *buf = NULL, *filename = get_history_file(info);

if (!filename)
return (0);

fd = open(filename, O_RDONLY);
free(filename);
if (fd == -1)
return (0);
if (!fstat(fd, &st))
file_size = st.st_size;
if (file_size < 2)
return (0);
buf = malloc(sizeof(char) * (file_size + 1));
if (!buf)
return (0);
read_len = read(fd, buf, file_size);
buf[file_size] = 0;
if (read_len <= 0)
return (free(buf), 0);
close(fd);
for (i = 0; i < file_size; i++)
if (buf[i] == '\n')
{
buf[i] = 0;
build_history_list(info, buf + last_line, line_count++);
last_line = i + 1;
}
if (last_line != i)
build_history_list(info, buf + last_line, line_count++);
free(buf);
info->histcount = line_count;
while (info->histcount-- >= HIST_MAX)
delete_node_at_index(&(info->history), 0);
renumber_history(info);
return (info->histcount);
}

/**
* build_history_list -function to add entry to a history linked list
* @info: pointer to the struct argument info
* @buf:pointer to buffer
* @line_count: the history line_count, histcount
*
* Return: Always 0
*/
int build_history_list(info_t *info, char *buf, int line_count)
{
list_t *node = NULL;

if (info->history)
node = info->history;
add_node_end(&node, buf, line_count);

if (!info->history)
info->history = node;
return (0);
}

/**
* renumber_history - function that renumber history linked list after changes
* @info: Structure containing potential arguments. Used to maintain
*
* Return: the new histcount
*/
int renumber_history(info_t *info)
{
list_t *node = info->history;
int i = 0;

while (node)
{
node->num = i++;
node = node->next;
}
return (info->histcount = i);
}

