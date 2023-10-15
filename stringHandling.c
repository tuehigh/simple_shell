#include "shell.h"

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

#include "shell.h"
/**
* _strcpy - function to copies a string
* @dst: the destination
* @src: the source
*
* Return: pointer to destination
*/
char *_strcpy(char *dst, char *src)
{
if (dst == src || src == 0)
return (dst);

for (int i = 0; src[i]; i++)
{
dst[i] = src[i];
}

dst[_strlen(src)] = 0;
return (dst);
}

/**
* _strdup- function that duplicates a string
* @str: the string to duplicate
*
* Return: pointer to the duplicated string
*/
char *_strdup(const char *str)
{
char *ret;
unsigned int length = 0;
int i;

if (str == NULL)
return (NULL);

while (*str++)
length++;
ret = malloc(sizeof(char) * (length + 1));

if (!ret)
return (NULL);
for (length++; length--;)
ret[length] = *--str;
return (ret);
}

/**
* _puts - function that prints an input string
* @str: the string to be printed
*
* Return: Nothing
*/
void _puts(char *str)
{
if (!str)
return;

for (int i = 0; str[i] != '\0'; i++)
{
_putchar(str[i]);
}
}

/**
* _putchar - function that writes the character c to stdout
* @c: The character to print
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int _putchar(char c)
{
static int i;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(1, buf, i);
i = 0;
}

if (c != BUF_FLUSH)
{
buf[i++] = c;
}

return (1);
}

