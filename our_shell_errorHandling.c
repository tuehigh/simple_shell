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

