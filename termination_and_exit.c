#include "our_own_shell.h"

/**
* _strncpy - Copy part of a string.
* @dst: Destination string.
* @src: Source string.
* @n: Maximum number of characters to copy.
*
* Copies src to dest, up to n characters
*     providing a pointer to the concatenated string.
* Return: result
*/
char *_strncpy(char *dst, char *src, int n)
{
	int si = 0;
	char *result = dst;

	for (int di = 0; src[si] != '\0' && si < n - 1; si++, di++)
	{
		dst[di] = src[si];
	}
	if (si < n)
	{
		for (int fi = si; fi < n; fi++)
		{
			dst[fi] = '\0';
		}
	}
	return (result);
}

/**
* _strncat - Concatenate two strings, limiting the number of characters.
* @dst: Destination string.
* @src: Source string.
* @n: Maximum number of characters to append.
*
* Appends src to dest, up to n characters,
*       and returns a pointer to the combined string.
* Return: result
*/
char *_strncat(char *dst, char *src, int n)
{
	int di = 0;
	int si = 0;
	char *result = dst;

	for (; dst[di] != '\0'; di++)
		;
	for (; src[si] != '\0' && si < n; si++, di++)
	{
		dst[di] = src[si];
	}
	if (si < n)
	{
		dst[di] = '\0';
	}
	return (result);
}

/**
* _strchr - Find the first occurrence of a character in a string.
* @str: Input string for searching.
* @c: Character to locate.
*
* Scans for the initial appearance of c
*     in str and returns a pointer to it, or NULL if not found.
* Return: null
*/
char *_strchr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');
	return (NULL);
}
