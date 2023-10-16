#include "our_own_shell.h"
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
