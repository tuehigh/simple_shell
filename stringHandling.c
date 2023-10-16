#include "our_own_shell.h"

/**
* _strlen - function to return the length of a string
* @str: The string whose length to check
*
* Return: Integer length of the string
*/
int _strlen(char *str)
{
int len = 0;

if (!str)
return (0);

for (; *str; str++)
len++;

return (len);
}

/**
* _strcmp -function to performs lexicographic comparison of two strings
* @str1: The first string
* @str2: The second string
*
* Return: Negative if str1 < str2,
*       positive if str1 > str2, zero if str1 == str2
*/
int _strcmp(char *str1, char *str2)
{
for (; *str1 && *str2; str1++, str2++)
{
if (*str1 != *str2)
return (*str1 - *str2);
}

if (*str1 == *str2)
return (0);
else
return (*str1 < *str2 ? -1 : 1);
}

/**
* starts_with - function that check if a string starts with a given substring
* @str: The string to search
* @substring: The substring to find
*
* Return: Address of the next character of the string or NULL
*/
char *starts_with(const char *str, const char *substring)
{
for (; *substring; str++, substring++)
{
if (*substring != *str)
return (NULL);
}
return ((char *)str);
}

/**
* _strcat - function that concatenates two strings
* @destination: The destination buffer
* @source: The source buffer
*
* Return: Pointer to the destination buffer
*/
char *_strcat(char *destination, char *source)
{
char *result = destination;

while (*destination)
destination++;

for (; *source; destination++, source++)
*destination = *source;

*destination = *source;

return (result);
}
