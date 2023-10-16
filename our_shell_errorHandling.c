#include "our_own_shell.h"

/**
* _eputs - function to Print an input
*        string to the standard error stream (stderr).
* @input_string: The string to be printed.
*
* This function writes the characters in the input string to stderr.
* If the input string is NULL, nothing is printed.
*
* Return: Nothing.
*/
void _eputs(char *input_string)
{
	if (!input_string)
		return;
	for (int index = 0; input_string[index] != '\0'; index++)
	{
		_eputchar(input_string[index]);
	}
}

/**
* _eputchar -funtion to Write the character
* to the standard error stream (stderr).
* @character: The character to print.
*This function writes a single character to the standard error stream.
* If the character is a control character
* (e.g., '\n' or '\t'), it may be buffered
* until a newline character is encountered, or the buffer is full.
*
* Return: On success,
* return 1 is returned. On error,
* return -1 is returned, and errno is set appropriately.
*/
int _eputchar(char character)
{
	static int buffer_index;
	static char write_buffer[WRITE_BUF_SIZE];

	if (character == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
	{
		write(2, write_buffer, buffer_index);
		buffer_index = 0;
	}
	if (character != BUF_FLUSH)
		write_buffer[buffer_index++] = character;
	return (1);
}

/**
* _putfd - Write the character c to the given file descriptor.
* @character: The character to print.
* @file_descriptor: The file descriptor to write to.
*
* This function writes a single character
* to the specified file descriptor.
* If the character is a control character
* (e.g., '\n' or '\t'), it may be buffered
* until a newline character is encountered, or the buffer is full.
*
* Return: On success,
* return 1 is returned. On error, -1 is returned,
* and errno is set appropriately.
*/
int _putfd(char character, int file_descriptor)
{
	static int buffer_index;
	static char write_buffer[WRITE_BUF_SIZE];

	if (character == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
	{
		write(file_descriptor, write_buffer, buffer_index);
		buffer_index = 0;
	}
	if (character != BUF_FLUSH)
		write_buffer[buffer_index++] = character;
	return (1);
}

/**
* _putsfd - Print an input string to the given file descriptor.
* @input_string: The string to be printed.
* @file_descriptor: The file descriptor to write to.
* This function writes the characters in the
* input string to the specified file descriptor.
* If the input string is NULL, nothing is printed.
* The function returns the number
* of characters written to the file descriptor.
*
* Return: The number of characters written.
*/
int _putsfd(char *input_string, int file_descriptor)
{
	int chars_written = 0;

	if (!input_string)
		return (0);
	for (int index = 0; input_string[index] != '\0'; index++)
	{
		chars_written += _putfd(input_string[index], file_descriptor);
	}
	return (chars_written);
}
#include "our_own_shell.h"

/**
* _erratoi -function that converts a string to an integer
* @str: the string to be converted
* Return: Converted number if successful, -1 on error
*/
int _erratoi(char *str)
{
int i = 0;
unsigned long int result = 0;

if (*str == '+')
str++;  /* TODO: why does this make main return 255? */
while (str[i] != '\0')
{
if (str[i] >= '0' && str[i] <= '9')
{
result *= 10;
result += (str[i] - '0');
if (result > INT_MAX)
return (-1);
}
else
return (-1);
i++;
}
return ((int)result);
}

/**
* print_error - function that prints an error message
* @info: the parameter & return info struct
* @error_str: string containing specified error type
*/
void print_error(info_t *info, char *error_str)
{
_eputs(info->fname);
_eputs(": ");
print_d(info->line_count, STDERR_FILENO);
_eputs(": ");
_eputs(info->argv[0]);
_eputs(": ");
_eputs(error_str);
}

/**
* print_d - function prints a decimal (integer) number (base 10)
* @number: the number to print
* @fd: the file descriptor to write to
* Return: number of characters printed
*/
int print_d(int number, int fd)
{
int (*__putchar)(char) = _putchar;
int i, count = 0;
unsigned int absolute, current;

if (fd == STDERR_FILENO)
__putchar = _eputchar;
if (number < 0)
{
absolute = (unsigned int)-number;
__putchar('-');
count++;
}
else
absolute = (unsigned int)number;
current = absolute;
i = 1000000000;
while (i > 1)
{
if (absolute / i)
{
__putchar('0' + current / i);
count++;
}
current %= i;
i /= 10;
}
__putchar('0' + current);
count++;

return (count);
}

/**
* convert_number -function that  convert function, a clone of itoa
* @num: number to be converted
* @base: base number
* @flags: argument flags
* Return:the string
*/
char *convert_number(long int num, int base, int flags)
{
static char *array;
static char buffer[50];
char sign = 0;
char *ptr;
unsigned long n = num;

if (!(flags & CONVERT_UNSIGNED) && num < 0)
{
n = -num;
sign = '-';
}
array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
ptr = &buffer[49];
*ptr = '\0';

while (n != 0)
{
*--ptr = array[n % base];
n /= base;
}

if (sign)
*--ptr = sign;
return (ptr);
}

/**
* remove_comments - function replaces the first instance of '#' with '\0'
* @input: address of the string to modify
*/
void remove_comments(char *input)
{
int i = 0;

while (input[i] != '\0')
{
if (input[i] == '#' && (!i || input[i - 1] == ' '))
{
input[i] = '\0';
break;
}
i++;
}
}

