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
