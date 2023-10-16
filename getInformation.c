#include "our_own_shell.h"

/**
* input_buf -finction to handles buffering chained commands.
* @info: Parameter structure.
* @buf: Address of the buffer.
* @buffer_len: Address of the buffer length.
*
* Return: The number of bytes read.
*/
ssize_t input_buf(info_t *info, char **buf, size_t *buffer_len)
{
ssize_t bytesRead = 0;
size_t currentLength = 0;

if (!*buffer_len)
{
free(*buf);
*buf = NULL;
signal(SIGINT, sigintHandler);
#if USE_GETLINE
bytesRead = getline(buf, &currentLength, stdin);
#else
bytesRead = _getline(info, buf, &currentLength);
#endif
if (bytesRead > 0)
{
if ((*buf)[bytesRead - 1] == '\n')
{
(*buf)[bytesRead - 1] = '\0';
bytesRead--;
}
info->linecount_flag = 1;
remove_comments(*buf);
build_history_list(info, *buf, info->histcount++);
}
}
return (bytesRead);
}

/**
* get_input -function to retrieves a line without the newline character.
* @info: Parameter structure.
*
* Return: The number of bytes read.
*/
ssize_t get_input(info_t *info)
{
static char *buf;
static size_t i, j, buffer_len;
ssize_t bytesRead = 0;
char **buf_ptr = &(info->arg), *p;

_putchar(BUF_FLUSH);
bytesRead = input_buf(info, &buf, &buffer_len);
if (bytesRead == -1)
return (-1);
if (buffer_len)
{
j = i;
p = buf + i;
check_chain(info, buf, &j, i, buffer_len);
for (; j < buffer_len; j++)
{
if (is_chain(info, buf, &j))
break;
}
i = j + 1;
if (i >= buffer_len)
{
i = buffer_len = 0;
info->cmd_buf_type = CMD_NORM;
}
*buf_ptr = p;
return (_strlen(p));
}
*buf_ptr = buf;
return (bytesRead);
}

/**
* read_buf - function to Reads a buffer.
* @info: Parameter structure.
* @buffer: Buffer.
* @size: Size.
*
* Return: r
*/
ssize_t read_buf(info_t *info, char *buffer, size_t *size)
{
ssize_t bytesRead = 0;

if (*size)
return (0);
bytesRead = read(info->readfd, buffer, READ_BUF_SIZE);
if (bytesRead >= 0)
*size = bytesRead;
return (bytesRead);
}

/**
* _getline - function to Gets the next line of input from STDIN.
* @info: Parameter structure.
* @ptr: Address of a pointer to the buffer, preallocated or NULL.
* @length: Size of the preallocated buffer if not NULL.
*
* Return: str
*/
int _getline(info_t *info, char **ptr, size_t *length)
{
static char buffer[READ_BUF_SIZE];
static size_t i, len;
size_t k;
ssize_t bytesRead = 0, str = 0;
char *_ptr = NULL, *new_ptr = NULL, *ch;

_ptr = *ptr;
if (_ptr && length)
str = *length;
if (i == len)
i = len = 0;
bytesRead = read_buf(info, buffer, &len);
if (bytesRead == -1 || (bytesRead == 0 && len == 0))
return (-1);
ch = _strchr(buffer + i, '\n');
k = ch ? 1 + (unsigned int)(ch - buffer) : len;
new_ptr = _realloc(_ptr, str, str ? str + k : k + 1);
if (!new_ptr) /* MALLOC FAILURE! */
return (_ptr ? free(_ptr), -1 : -1);
if (str)
_strncat(new_ptr, buffer + i, k - i);
else
_strncpy(new_ptr, buffer + i, k - i + 1);
str += k - i;
i = k;
_ptr = new_ptr;
if (length)
*length = str;
*ptr = _ptr;
return (str);
}

/**
* sigintHandler - function for the Blocks Ctrl-C.
* @sig_num: Signal number.
*
* Return: void
*/
void sigintHandler(__attribute__((unused))int sig_num)
{
_puts("\n");
_puts("$ ");
_putchar(BUF_FLUSH);
}
