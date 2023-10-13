#include "shell.h"

/**
* interactive -function that returns true if shell is in interactive mode
* @inf:pointer to  struct info
*
* Return: 1 if interactive mode, 0 otherwise
*/
int interactive(info_t *inf)
{
return (isatty(STDIN_FILENO) && inf->readfd <= 2);
}

/**
* is_delim - function that checks if character is a delimiter
* @ch: the character to check
* @del: pointer to the delimiter string
* Return: 1 if true, 0 if false
*/
int is_delim(char ch, char *del)
{
while (*del)
{
if (*del == ch)
return (1);
del++;
}
return (0);
}

/**
* _isalpha - function that checks for alphabetic character
* @character: The character to input
* Return: 1 if c is alphabetic, 0 otherwise
*/
int _isalpha(int character)
{
if ((character >= 'a' && character <= 'z')
|| (character >= 'A' && character <= 'Z'))
return (1);
else
return (0);
}

/**
* _atoi -function that converts a string to an integer
* @str:pointer to the string to be converted
* Return: 0 if no numbers in string, converted number otherwise
*/
int _atoi(char *str)
{
int i, sign = 1, flag = 0, output;
unsigned int result = 0;

i = 0;
while (str[i] != '\0' && flag != 2)
{
if (str[i] == '-')
sign *= -1;

if (str[i] >= '0' && str[i] <= '9')
{
flag = 1;
result *= 10;
result += (str[i] - '0');
}
else if (flag == 1)
flag = 2;
i++;
}

if (sign == -1)
output = -result;
else
output = result;

return (output);
}
