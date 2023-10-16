#include "our_own_shell.h"

/**
* _memset - function that fills memory with a constant byte
* @dest: Pointer to the memory area
* @ch: The byte to fill @dest with
* @n: The number of bytes to be filled
* Return: A pointer to the memory area @dest
*/
char *_memset(char *dest, char ch, unsigned int n)
{
	unsigned int i = 0;

	while (i < n)
	{
		dest[i] = ch;
		i++;
	}
	return (dest);
}

/**
* ffree -function that frees a string of strings
* @str_arr: String array to free
*/
void ffree(char **str_arr)
{
	char **arr = str_arr;

	if (!str_arr)
		return;
	while (*str_arr)
	{
		free(*str_arr);
		str_arr++;
	}
	free(arr);
}

/**
* _realloc - function that reallocates a block of memory
* @prev_ptr: Pointer to the previous malloc'ed block
* @old_size: Byte size of the previous block
* @new_size: Byte size of the new block
*
* Return: A pointer to the reallocated block of memory.
*/
void *_realloc(void *prev_ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!prev_ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(prev_ptr), NULL);
	if (new_size == old_size)
		return (prev_ptr);
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	while (old_size)
	{
		new_ptr[old_size - 1] = ((char *)prev_ptr)[old_size - 1];
		old_size--;
	}
	free(prev_ptr);
	return (new_ptr);
}
